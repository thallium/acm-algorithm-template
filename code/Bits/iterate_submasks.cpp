for (int sub = mask; ; sub = (sub - 1) & mask) {
    printf("%3d: ", sub);
    if (sub == 0) break; // move this to loop condition if you don't want 0
}
