import React from 'react'
import moment from 'moment'
import { bindActionCreators } from 'redux'
import { connect } from 'react-redux'
import Layout from './layout'
import { loadSubmissions } from './redux/actions'
import { history } from './history'

class Submissions extends React.Component {

  componentWillMount () {
    if (!this.props.user) {
      history.push('/login')
      return
    }
    if (!this.props.submissions.length) {
      this.props.loadSubmissions()
    }
  }

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
      <Layout>
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
                  <td>{moment.unix(item.created).format('DD/MM/YYYY HH:mm::ss')}</td>
                  <td>{this.renderStatus(item)}</td>
                </tr>
              )
            })
          }
          </tbody>
        </table>
      </Layout>
    )
  }
}

const mapStateToProps = (state, props) => ({
  submissions: state.submission,
  user: state.app.user,
})

const mapDispatchToProps = (dispatch) => bindActionCreators({
  loadSubmissions
}, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(Submissions)