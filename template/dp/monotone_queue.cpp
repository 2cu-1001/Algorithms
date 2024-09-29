for (int i = 1; i <= N; i++) {
        cin >> cur;
        while (!mq.empty() && mq.back().first > cur) mq.pop_back();
        while (!mq.empty() && i - mq.front().second > L - 1) mq.pop_front();
        mq.push_back({ cur, i });
        cout << mq.front().first << " ";
    }