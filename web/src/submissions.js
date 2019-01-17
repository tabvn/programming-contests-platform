import React from 'react'
import moment from 'moment'
export default class Submissions extends React.Component {

  renderStatus = (s) => {
    if (s.status === 0) {
      return <div className={'status-sent'}>Submitted</div>
    }

    if (s.status === 1) {
      return <div className={'status-queue'}>Queued</div>
    }

    if (s.status === 2) {

      if (s.error) {
        return <div className={'status-error'}>{s.error}</div>
      }
      if (s.accepted) {
        return <div
          className={'status-accepted'}>Accepted</div>
      }

    }

  }

  render () {
    const {submissions} = this.props

    return (
      <table>
        <thead>
        <tr>
          <th>Problem</th>
          <th>Score</th>
          <th>Time</th>
          <th>Status</th>
        </tr>
        </thead>
        <tbody>
        {
          submissions.map((item, k) => {
            return (
              <tr key={k}>
                <td>{item.problem}</td>
                <td>{item.score}</td>
                <td>{moment.unix(item.created).format("DD/MM/YYYY HH:mm::ss")}</td>
                <td>{this.renderStatus(item)}</td>
              </tr>
            )
          })
        }
        </tbody>
      </table>
    )
  }
}