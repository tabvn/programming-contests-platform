import { NEW_SUBMISSION, SET_MESSAGE, SET_PROBLEMS, SET_SCOREBOARD, SET_SUBMISSIONS, SET_USER } from '../types'
import service from '../../service'

let timer

export const logout = () => {
  return (dispatch, getState, {service}) => {

    dispatch({
      type: SET_USER,
      payload: null
    })

    service.logout()
  }
}

export const setMessage = (message, type = 'error') => {
  return (dispatch) => {

    dispatch({
      type: SET_MESSAGE,
      payload: {
        type: type,
        body: message,
      },
    })

    if (timer) {
      clearTimeout(timer)
    }
    timer = setTimeout(() => {

      dispatch({
        type: SET_MESSAGE,
        payload: null
      })
    }, 5000)
  }
}

export const loadSubmissions = () => {

  return (dispatch, getState, {service}) => {

    service.get('api/my-submissions').then((res) => {

      dispatch({
        type: SET_SUBMISSIONS,
        payload: res.data,
      })
    }).catch((e) => {
      dispatch(setMessage('An error loading your submissions.', 'error'))
    })
  }
}

export const loadScoreboard = () => {

  return (dispatch, getState, {service}) => {

    service.get('api/scoreboard').then((res) => {

      dispatch({
        type: SET_SCOREBOARD,
        payload: res.data,
      })
    }).catch((e) => {

      if (e.response && e.response.status && e.response.status === 401) {

        dispatch({
          type: SET_USER,
          payload: null
        })
        service.logout()

        dispatch(setMessage('Access denied'))

      }

      dispatch(setMessage('An error loading scoreboard'))
    })
  }
}

export const loadProblems = () => {

  return (dispatch, getState, {service}) => {

    service.get('api/problems').then((res) => {
      dispatch({
        type: SET_PROBLEMS,
        payload: res.data,
      })
    }).catch((e) => {

      if (e.response && e.response.status && e.response.status === 401) {

        dispatch({
          type: SET_USER,
          payload: null
        })

        service.logout()

        dispatch(setMessage('Access denied'))

      } else {
        dispatch(setMessage('An error loading problems.'))
      }

    })
  }
}

export const solveProblem = (name, code) => {

  return (dispatch, getState, {service}) => {

    return new Promise((resolve, reject) => {

      service.solveProblem(name, code).then((data) => {

        dispatch({
          type: NEW_SUBMISSION,
          payload: data,
        })

        return resolve(data)

      }).catch((e) => {
        if (e.response && e.response.status && e.response.status === 401) {

          dispatch({
            type: SET_USER,
            payload: null
          })
          service.logout()

          dispatch(setMessage('Your submission could not be saved.'))

        } else {
          dispatch(setMessage('Your submission could not be saved.'))
        }

        return reject(e)

      })
    })
  }
}

export const login = (id, password) => {

  return (dispatch, getState, {service}) => {

    return new Promise((resolve, reject) => {

      service.auth(id, password).then((user) => {

        const data = {
          action: 'auth',
          payload: user.token,
        }

        service.send(data)

        dispatch({
          type: SET_USER,
          payload: user
        })
        dispatch(loadProblems())

        return resolve(user)

      }).catch((e) => {

        let msg = 'Login error'
        if (e.response && e.response.data && e.response.data.message) {
          msg = e.response.data.message
        }
        return reject(msg)
      })

    })
  }
}