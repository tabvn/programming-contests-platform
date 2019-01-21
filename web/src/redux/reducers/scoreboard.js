import { SET_SCOREBOARD } from '../types'

export default (state = [], action) => {

  switch (action.type) {

    case SET_SCOREBOARD:

      return action.payload

    default:

      return state
  }
}