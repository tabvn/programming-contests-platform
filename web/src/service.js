import axios from 'axios'
import { loadScoreboard } from './redux/actions'
import { UPDATE_SUBMISSION } from './redux/types'

let ws
let queue = []

class Service {

  constructor () {

    this.url = '/'
    this.user = this.getUserFromLocalStore()
    this.store = null

  }

  send (message) {

    if (ws && ws.readyState === 1) {
      ws.send(JSON.stringify(message))
    } else {

      queue.push(message)

      if (!ws) {

        this.connect()
      }
    }
  }

  connect () {

    if (typeof window.Ued === 'undefined') {
      console.log('No websocket url')
      return
    }
    ws = new WebSocket(`${window.Ued.ws}`)
    ws.onopen = () => {

      // check queue and send
      if (this.user) {
        ws.send(JSON.stringify({
          action: 'auth',
          payload: this.user.token,
        }))
      }
      queue.forEach((p) => {
        ws.send(JSON.stringify(p))
      })

      queue = []
    }
    ws.onmessage = (event) => {

      const data = event.data

      try {

        const message = JSON.parse(data)
        switch (message.action) {
          case 'reload':
            this.store.dispatch(loadScoreboard())
            break

          case 'submission':

            this.store.dispatch({
              type: UPDATE_SUBMISSION,
              payload: message.payload
            })

            break

          default:

            break
        }

      } catch (e) {
        console.log('an error parser message', e)
      }

    }
    ws.onclose = () => {
      this.connect()
    }
    ws.onerror = () => {
      this.connect()
    }
  }

  logout () {

    this.post('api/logout')
    this.user = null
    axios.defaults.headers.common['Authorization'] = ''
    localStorage.removeItem('ued_user')
  }

  getUserFromLocalStore () {
    const str = localStorage.getItem('ued_user')
    if (str) {
      const u = JSON.parse(str)
      axios.defaults.headers.common['Authorization'] = u.token

      return u
    }

    return null
  }

  auth (id, password) {

    return new Promise((resolve, reject) => {
      this.post('api/login', {id: id, password: password}).then((res) => {
        this.user = res.data

        axios.defaults.headers.common['Authorization'] = this.user.token
        localStorage.setItem('ued_user', JSON.stringify(this.user))
        return resolve(res.data)

      }).catch((e) => {
        return reject(e)
      })

    })
  }

  solveProblem (name, code) {

    return new Promise((resolve, reject) => {
      this.post('api/solve', {problem: name, code: code}).then((res) => {
        return resolve(res.data)
      }).catch((e) => {
        if (e.response && e.response.status && e.response.status === 401) {

          this.user = null
          axios.defaults.headers.common['Authorization'] = ''
          localStorage.removeItem('ued_user')

        }
        if (e.status) {

        }
        return reject(e)
      })
    })
  }

  getUrl (path) {
    return `${this.url}${path}`
  }

  get (path) {

    return axios.get(this.getUrl(path))
  }

  post (path, data) {
    return axios.post(this.getUrl(path), JSON.stringify(data))
  }

}

export default Service