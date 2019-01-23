import thunk from 'redux-thunk'
import { createStore, applyMiddleware } from 'redux'
import reducers from './reducers'
import Service from '../service'
import { loadProblems } from './actions'
import { SET_USER } from './types'

const service = new Service()

export const store = createStore(
  reducers,
  applyMiddleware(thunk.withExtraArgument({service}))
)

service.store = store

service.connect();

if (service.user) {

  store.dispatch({
    type: SET_USER,
    payload: service.user
  })

  store.dispatch(loadProblems())

}

