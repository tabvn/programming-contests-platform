import { SET_PROBLEMS } from '../types'

export default (state = [], action) => {

  switch (action.type) {

    case SET_PROBLEMS:

      return action.payload

    default:

      return state
  }
}