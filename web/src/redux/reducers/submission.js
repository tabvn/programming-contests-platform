import { NEW_SUBMISSION, SET_SUBMISSIONS, UPDATE_SUBMISSION } from '../types'

export default (state = [], action) => {

  switch (action.type) {

    case SET_SUBMISSIONS:
      return action.payload

    case NEW_SUBMISSION:

      return [action.payload].concat(state)

    case UPDATE_SUBMISSION:

      let submissions = state

      const index = submissions.findIndex((s) => s.id === action.payload.id)
      if (index !== -1) {
        submissions[index] = action.payload
      }


      return state.map((s) => {
        if (s.id === action.payload.id) {
          return {
            ...s,
            accepted: action.payload.accepted,
            error: action.payload.error,
            created: action.payload.created,
            score: action.payload.score,
            status: action.payload.status
          }
        }

        return s
      })

    default:

      return state
  }
}