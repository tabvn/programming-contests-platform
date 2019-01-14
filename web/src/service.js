import axios from 'axios'

class Service {

  constructor () {
    this.url = '/'
    this.user = null
  }

  auth (id, password) {

    return new Promise((resolve, reject) => {
      this.post('api/login', {id: id, password: password}).then((res) => {
        this.user = res.data
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