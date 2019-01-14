import axios from 'axios'

class Service {

  constructor () {
    this.url = '/'
    this.user = this.getUserFromLocalStore()

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

export default new Service()