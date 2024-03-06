import sys

def fcfs(y, arr):
    i, j = 0, 0
    start, end = arr[1], arr[1]
    temp = 0
    endTime = [0] * y
    startTime = [0] * y

    with open("fcfs.txt", "w") as file:
        for i in range(y):
            start = end
            startTime[i] = start
            end += arr[j * 3 + 2]
            endTime[i] = end
            temp += start - arr[i * 3 + 1]
            j += 1
            print(f"P[{arr[i * 3]}] Start time: {startTime[i]} End time: {endTime[i]} | Waiting time: {startTime[i] - arr[i * 3 + 1]}")
            file.write(f"P[{arr[i * 3]}] Start time: {startTime[i]} End time: {endTime[i]} | Waiting time: {startTime[i] - arr[i * 3 + 1]}\n")

        print(f"Average waiting time: {temp / y:.1f}")
        file.write(f"Average waiting time: {temp / y:.1f}")


def round_robin(size, splice, arr):
    i, j, k = 0, 0, 0
    time, burst = 0, 0
    startTime = arr[1]
    endTime = arr[1]
    waitTime = [0] * size
    output = [""] * size
    check = False
    aveWait = 0

    with open("RR.txt", "w") as file:
        for i in range(size):
            output[i] = f"P[{arr[i * 3]}] "

        while True:
            check = False
            for i in range(size):
                if arr[i * 3 + 2] > 0:
                    startTime = endTime
                    burst = arr[i * 3 + 2]
                    arr[i * 3 + 2] -= splice

                    if burst - splice <= 0:
                        endTime += burst

                        if i > 0:
                            waitTime[i] = startTime - arr[i * 3 + 1]
                            aveWait += waitTime[i]
                        else:
                            waitTime[i] = 0

                        output[i] += f"Start time: {startTime} End time: {endTime} | Waiting time: {waitTime[i]}\n"
                    else:
                        endTime += splice
                        output[i] += f"Start time: {startTime} End time: {endTime} |"
                        check = True

            if not check:
                break

        for i in range(size):
            print(output[i])
            file.write(output[i] + "\n")

        print(f"Average waiting time: {aveWait / size:.1f}")
        file.write(f"Average waiting time: {aveWait / size:.1f}")


def srtf(size, arr):
    i, j = 0, 0
    time, burst = arr[1], 0
    startTime = arr[1]
    endTime = arr[1]
    waitTime = [0] * size
    output = [""] * size
    check = False
    min_val, min_index, prev_min = 99999999, 0, 0
    complete = 0
    counter = 0
    order = [0] * size
    bt = [0] * size
    aveWait = 0

    with open("srtf.txt", "w") as file:
        for i in range(size):
            output[i] = f"P[{arr[i * 3]}] "
            bt[i] = arr[i * 3 + 2]

        while complete < size:
            for i in range(size):
                if arr[i * 3 + 1] <= time and arr[i * 3 + 2] < min_val and arr[i * 3 + 2] > 0:
                    min_val = arr[i * 3 + 2]
                    min_index = i
                    check = True

            if check:
                startTime = time
                output[min_index] += f"Start time: {startTime} "
                if counter > 0:
                    endTime = time
                    output[prev_min] += f"End time: {endTime} | "
                prev_min = min_index
                counter += 1
                check = False

            arr[min_index * 3 + 2] -= 1
            min_val -= 1
            time += 1

            if min_val == 0:
                min_val = 99999999
                complete += 1
                order[j] = min_index
                waitTime[j] = time - arr[min_index * 3 + 1] - bt[min_index]
                aveWait += waitTime[j]
                j += 1

        output[min_index] += f"End time: {time} | "
        for i in range(size):
            output[order[i]] += f"Wait Time: {waitTime[i]}\n"
            print(output[order[i]])
            file.write(output[order[i]] + "\n")

        print(f"Average waiting time: {aveWait / size:.1f}")
        file.write(f"Average waiting time: {aveWait / size:.1f}")


def sjf(size, arr):
    i, j = 0, 0
    time, burst = arr[1], 0
    startTime = arr[1]
    endTime = arr[1]
    waitTime = [0] * size
    output = [""] * size
    check = False
    min_val, min_index, prev_min = 99999999, 0, 0
    complete = 0
    order = [0] * size
    bt = [0] * size
    aveWait = 0

    with open("sjf.txt", "w") as file:
        for i in range(size):
            output[i] = f"P[{arr[i * 3]}]"
            bt[i] = arr[i * 3 + 2]

        while complete < size:
            for i in range(size):
                if arr[i * 3 + 2] < min_val and arr[i * 3 + 2] > 0 and arr[i * 3 + 1] <= endTime:
                    min_val = arr[i * 3 + 2]
                    min_index = i

            output[min_index] += f"Start time: {endTime} "
            endTime += arr[min_index * 3 + 2]
            arr[min_index * 3 + 2] = 0
            output[min_index] += f"End time: {endTime} | "
            order[j] = min_index
            waitTime[min_index] = endTime - arr[min_index * 3 + 1] - bt[min_index]
            aveWait += waitTime[min_index]
            j += 1
            min_val = 999999999
            complete += 1

        for i in range(size):
            output[order[i]] += f"Wait Time: {waitTime[order[i]]}\n"
            print(output[order[i]])
            file.write(output[order[i]] + "\n")

        print(f"Average waiting time: {aveWait / size:.1f}")
        file.write(f"Average waiting time: {aveWait / size:.1f}")


def main():
    filename = input("Input filename: ")
    filename += ".txt"

    try:
        with open(filename, "r") as file:
            x, y, z = map(int, file.readline().split())
            arr = [int(num) for num in file.read().split()]
            main_scheduler(x, y, z, arr)
    except FileNotFoundError:
        print(f"{filename} not found.")


def main_scheduler(x, y, z, arr):
    if x == 0:
        fcfs(y, arr)
    elif x == 1:
        sjf(y, arr)
    elif x == 2:
        srtf(y, arr)
    elif x == 3:
        round_robin(y, z, arr)


if __name__ == "__main__":
    main()
