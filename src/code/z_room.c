#include <ultra64.h>
#include <global.h>
#include <macros.h>

void func_80095AB4(GlobalContext* globalCtx, Room* room, u32 flags);
void func_80095D04(GlobalContext* globalCtx, Room* room, u32 flags);
void func_80096F6C(GlobalContext* globalCtx, Room* room, u32 flags);

Vec3f D_801270A0 = { 0.0f, 0.0f, 0.0f };

// unused
Gfx D_801270B0[] =
{
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE, 0, 0, 0, SHADE),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP |
                     G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPClipRatio(FRUSTRATIO_1),
    gsSPEndDisplayList(),
};

void (*sRoomDrawHandlers[])(GlobalContext* globalCtx, Room* room, u32 flags) =
{
    func_80095AB4,
    func_80096F6C,
    func_80095D04,
};

UNK_TYPE D_8012711C = 0;

void func_80095AA0(GlobalContext* globalCtx, Room* room, UNK_TYPE arg2, UNK_TYPE arg3)
{

}

// Room Draw Polygon Type 0
void func_80095AB4(GlobalContext* globalCtx, Room* room, u32 flags)
{
    s32 i;
    PolygonType0* polygon0;
    PolygonDlist* polygonDlist;
    GraphicsContext* gfxCtx;
    Gfx* gfxArr[4];

    gfxCtx = globalCtx->gfxCtx;
    func_800C6AC4(gfxArr, globalCtx->gfxCtx, "../z_room.c", 193);

    if (flags & 1)
    {
        func_800342EC(&D_801270A0, globalCtx);
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);
        func_80093C80(globalCtx);
        gSPMatrix(gfxCtx->polyOpa.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & 2)
    {
        func_8003435C(&D_801270A0, globalCtx);
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_80093D84(globalCtx->gfxCtx);
        gSPMatrix(gfxCtx->polyXlu.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    polygon0 = &room->mesh->polygon0;
    polygonDlist = SEGMENTED_TO_VIRTUAL(polygon0->start);
    for (i = 0; i < polygon0->num; i++)
    {
        if ((flags & 1) && (polygonDlist->opa != NULL))
            gSPDisplayList(gfxCtx->polyOpa.p++, polygonDlist->opa);

        if ((flags & 2) && (polygonDlist->xlu != NULL))
            gSPDisplayList(gfxCtx->polyXlu.p++, polygonDlist->xlu);

        polygonDlist++;
    }

    func_800C6B54(gfxArr, globalCtx->gfxCtx, "../z_room.c", 239);
}

#define SHAPE_SORT_MAX 64

typedef struct struct_80095D04
{
    /* 0x00 */ PolygonDlist2* unk_00;
    /* 0x04 */ f32            unk_04;
    /* 0x08 */ struct struct_80095D04* unk_08;
    /* 0x0C */ struct struct_80095D04* unk_0C;
} struct_80095D04; // size = 0x10

// Room Draw Polygon Type 2
#ifdef NON_MATCHING
// this function still needs some work
void func_80095D04(GlobalContext* globalCtx, Room* room, u32 flags)
{
    PolygonType2* polygon2;
    PolygonDlist2* polygonDlist;
    struct_80095D04 spB8[SHAPE_SORT_MAX];
    struct_80095D04* spB4;
    struct_80095D04* spB0;
    struct_80095D04* phi_v0;
    struct_80095D04* phi_a0;
    struct_80095D04* spA4;
    s32 phi_v1;
    s32 sp9C;
    Vec3f sp90;
    Vec3f sp84;
    f32 sp80;
    PolygonDlist2* phi_s0;
    PolygonDlist2* sp78;
    f32 temp_f0;
    f32 temp_f2;
    GraphicsContext* gfxCtx;
    Gfx* sp5C[4];

    spB0 = NULL;
    spB4 = NULL;
    gfxCtx = globalCtx->gfxCtx;
    func_800C6AC4(sp5C, globalCtx->gfxCtx, "../z_room.c", 287);

    if (flags & 1)
    {
        func_800342EC(&D_801270A0, globalCtx);
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);
        func_80093C80(globalCtx);
        gSPMatrix(gfxCtx->polyOpa.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    if (flags & 2)
    {
        func_8003435C(&D_801270A0, globalCtx);
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_80093D84(globalCtx->gfxCtx);
        gSPMatrix(gfxCtx->polyXlu.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
    }

    spA4 = &spB8[0];
    polygonDlist = SEGMENTED_TO_VIRTUAL(room->mesh->polygon2.start);
    polygon2 = &room->mesh->polygon2;
    if (polygon2->num > SHAPE_SORT_MAX)
        __assert("polygon2->num <= SHAPE_SORT_MAX", "../z_room.c", 317);

    sp78 = polygonDlist;
    for (sp9C = 0; sp9C < polygon2->num; sp9C++)
    {
        sp90.x = polygonDlist->pos.x;
        sp90.y = polygonDlist->pos.y;
        sp90.z = polygonDlist->pos.z;
        func_800A6E10(globalCtx->mf_11D60, &sp90, &sp84, &sp80);
        temp_f0 = polygonDlist->unk_06;
        if (-temp_f0 < sp84.z)
        {
            temp_f2 = sp84.z - temp_f0;
            if (temp_f2 < globalCtx->lightCtx.unkC)
            {
                spA4->unk_00 = polygonDlist;
                spA4->unk_04 = temp_f2;
                phi_v0 = spB4;
                if (spB4 == 0)
                {
                    spB0 = spA4;
                    spB4 = spA4;
                    spA4->unk_0C = NULL;
                    spA4->unk_08 = NULL;
                }
                else
                {
                    do
                    {
                        if (spA4->unk_04 < phi_v0->unk_04)
                            break;
                        phi_v0 = phi_v0->unk_0C;
                    } while (phi_v0 != NULL);

                    if (phi_v0 == NULL)
                    {
                        spA4->unk_08 = spB0;
                        spA4->unk_0C = NULL;
                        spB0->unk_0C = spA4;
                        spB0 = spA4;
                    }
                    else
                    {
                        phi_a0 = phi_v0->unk_08;
                        spA4->unk_08 = phi_a0;
                        if (phi_a0 == NULL)
                            spB4 = spA4;
                        else
                            phi_a0->unk_0C = spA4;
                        phi_v0->unk_08 = spA4;
                        spA4->unk_0C = (void *) phi_v0;
                    }
                }
                spA4 = spA4++;
            }
        }
        polygonDlist++;
    }

    gGameInfo->unk_D82 = polygon2->num;

    sp9C = 1;
    while (spB4 != NULL)
    {
        phi_s0 = spB4->unk_00;
        if (gGameInfo->unk_D80 != 0)
        {
            phi_v1 = 0;
            while (phi_v1 < polygon2->num)
            {
                if (phi_s0 == sp78)
                    break;
                phi_v1++;
                sp78++;
            }

            if (((gGameInfo->unk_D80 == 1) && (gGameInfo->unk_D86 > sp9C)) ||
                ((gGameInfo->unk_D80 == 2) && (gGameInfo->unk_D86 == sp9C)))
            {
                if ((flags & 1) && (phi_s0->opa != NULL))
                    gSPDisplayList(gfxCtx->polyOpa.p++, phi_s0->opa);

                if ((flags & 2) && (phi_s0->xlu != NULL))
                    gSPDisplayList(gfxCtx->polyXlu.p++, phi_s0->xlu);
            }
        }
        else
        {
            if ((flags & 1) && (phi_s0->opa != NULL))
                gSPDisplayList(gfxCtx->polyOpa.p++, phi_s0->opa);

            if ((flags & 2) && (phi_s0->xlu != NULL))
                gSPDisplayList(gfxCtx->polyXlu.p++, phi_s0->xlu);
        }

        spB4 = spB4->unk_0C;
        sp9C++;
    }

    gGameInfo->unk_D84 = sp9C - 1;

    func_800C6B54(sp5C, globalCtx->gfxCtx, "../z_room.c", 430);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_80095D04.s")
#endif

#define JPEG_MARKER 0xFFD8FFE0

#ifdef NON_MATCHING
// long multiplication by 64 doesn't quite match
s32 func_80096238(void* data)
{
    OSTime timeBefore;
    OSTime timeAfter;
    OSTime time;

    if (*(u32*)data == JPEG_MARKER)
    {
        // Translates to: "EXPANDING JPEG DATA"
        osSyncPrintf("JPEGデータを展開します\n");
        // Translates to: "JPEG DATA ADDRESS %08x"
        osSyncPrintf("JPEGデータアドレス %08x\n", data);
        // Translates to: "WORK BUFFER ADDRESS (Z BUFFER) %08x"
        osSyncPrintf("ワークバッファアドレス（Ｚバッファ）%08x\n", gZBuffer);

        timeBefore = osGetTime();
        if (!func_8006E418(data, gZBuffer, D_8019B1C0, sizeof(D_8019B1C0)))
        {
            timeAfter = osGetTime();
            time = ((timeAfter - timeBefore) * 64) / 3000;

            // Translates to: "SUCCESS... I THINK. time = %6.3f ms"
            osSyncPrintf("成功…だと思う。 time = %6.3f ms \n", (f64)(time / 1000.0f));
            // Translates to: "WRITING BACK TO ORIGINAL ADDRESS FROM WORK BUFFER."
            osSyncPrintf("ワークバッファから元のアドレスに書き戻します。\n");
            // Translates to: "IF THE ORIGINAL BUFFER SIZE ISN'T AT LEAST 150KB, IT WILL BE OUT OF CONTROL."
            osSyncPrintf("元のバッファのサイズが150キロバイト無いと暴走するでしょう。\n");

            bcopy(gZBuffer, data, sizeof(gZBuffer));
        }
        else
        {
            // Translates to: "FAILURE! WHY IS IT U+301C"
            osSyncPrintf("失敗！なんでU+301C\n");
        }
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_80096238.s")
#endif

#ifdef NON_MATCHING
// pointer arithmetic doesn't quite match
void func_8009638C(Gfx** displayList, u32 source, u32 tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 mode0, u16 tlutCount, f32 frameX, f32 frameY)
{
    Gfx* displayListHead;
    uObjBg* bg;

    displayListHead = *displayList;
    func_80096238(SEGMENTED_TO_VIRTUAL(source));

    displayListHead++;
    gSPBranchList(displayListHead, displayListHead+5);
    bg = (void*)displayListHead;
    bg->b.imageX = 0;
    bg->b.imageW = width * 4;
    bg->b.frameX = frameX * 4;
    bg->b.imageY = 0;
    bg->b.imageH = height * 4;
    bg->b.frameY = frameY * 4;
    bg->b.imagePtr = (void*)source;
    bg->b.imageLoad = G_BGLT_LOADTILE;
    bg->b.imageFmt = fmt;
    bg->b.imageSiz = siz;
    bg->b.imagePal = 0;
    bg->b.imageFlip = 0;

    if (fmt == G_IM_FMT_CI)
    {
        displayListHead = (void*)(bg+1);
        gDPLoadTLUT(displayListHead++, tlutCount, 256, tlut);
    }
    else
    {
        displayListHead = (void*)(bg+1);
        gDPPipeSync(displayListHead++);
    }

    if ((fmt == G_IM_FMT_RGBA) && (gGameInfo->unk_108 == 0))
    {
        bg->b.frameW = width * 4;
        bg->b.frameH = height * 4;
        func_80104B00(bg);
        gDPSetOtherMode(displayListHead++,
                        mode0 | G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT |
                        G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                        G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
        gSPBgRectCopy(displayListHead++, bg);
    }
    else
    {
        bg->s.frameW = width * 4;
        bg->s.frameH = height * 4;
        bg->s.scaleW = 1024;
        bg->s.scaleH = 1024;
        bg->s.imageYorig = bg->b.imageY;
        gDPSetOtherMode(displayListHead++,
                        mode0 | G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT |
                        G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_THRESHOLD | G_ZS_PIXEL | AA_EN |
                        CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL |
                        GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                        GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA));
        gDPSetCombineLERP(displayListHead++,
                          0, 0, 0, TEXEL0, 0, 0, 0, 1,
                          0, 0, 0, TEXEL0, 0, 0, 0, 1);
        gSPObjRenderMode(displayListHead++, 0x0C); // unknown object render mode?
        gSPBgRect1Cyc(displayListHead++, bg);
    }

    gDPPipeSync(displayListHead++);
    *displayList = displayListHead;
}
#else
void func_8009638C(Gfx** displayList, u32 source, u32 tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 mode0, u16 tlutCount, f32 frameX, f32 frameY);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_8009638C.s")
#endif

// Room Draw Polygon Type 1 - Single Format
void func_80096680(GlobalContext* globalCtx, Room* room, u32 flags)
{
    Camera* camera;
    Gfx* spA8;
    PolygonType1* polygon1;
    PolygonDlist* polygonDlist;
    u32 sp9C;
    u32 sp98;
    u32 sp94;
    u32 sp90;
    GraphicsContext* gfxCtx;
    Gfx* gfxArr[4];

    gfxCtx = globalCtx->gfxCtx;
    func_800C6AC4(gfxArr, globalCtx->gfxCtx, "../z_room.c", 628);

    camera = globalCtx->cameraCtx.activeCameraPtrs[globalCtx->cameraCtx.unk_5C0];
    polygon1 = &room->mesh->polygon1;
    sp9C = (camera->unk_142 ^ 0x19) < 1U;
    polygonDlist = SEGMENTED_TO_VIRTUAL(polygon1->dlist);
    sp98 = (flags & 1) && sp9C && polygon1->single.source && !(gGameInfo->unk_106 & 1);
    sp94 = (flags & 1) && polygonDlist->opa && !(gGameInfo->unk_106 & 2);
    sp90 = (flags & 2) && polygonDlist->xlu && !(gGameInfo->unk_106 & 4);

    if (sp94 || sp98)
    {
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);

        if (sp94)
        {
            func_80093D18(globalCtx->gfxCtx);
            gSPMatrix(gfxCtx->polyOpa.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(gfxCtx->polyOpa.p++, polygonDlist->opa);
        }

        if (sp98)
        {
            // gSPLoadUcodeL(gfxCtx->polyOpa.p++, rspS2DEX)?
            gSPLoadUcodeEx(gfxCtx->polyOpa.p++, D_00113070, D_001579A0, 0x800);

            if (1)
            {
                Vec3f sp60;
                spA8 = gfxCtx->polyOpa.p;
                func_8005AFB4(&sp60, camera);
                func_8009638C(&spA8, polygon1->single.source, polygon1->single.tlut,
                              polygon1->single.width, polygon1->single.height,
                              polygon1->single.fmt, polygon1->single.siz,
                              polygon1->single.mode0, polygon1->single.tlutCount,
                              (sp60.x + sp60.z) * 1.2f + sp60.y * 0.6f,
                              sp60.y * 2.4f + (sp60.x + sp60.z) * 0.3f);
                gfxCtx->polyOpa.p = spA8;
            }

            // gSPLoadUcode(gfxCtx->polyOpa.p++, func_800D2E14(), func_800D2E20())?
            gSPLoadUcodeEx(gfxCtx->polyOpa.p++, func_800D2E14(), func_800D2E20(), 0x800);
        }
    }

    if (sp90)
    {
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_80093D84(globalCtx->gfxCtx);
        gSPMatrix(gfxCtx->polyXlu.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
        gSPDisplayList(gfxCtx->polyXlu.p++, polygonDlist->xlu);
    }

    func_800C6B54(gfxArr, globalCtx->gfxCtx, "../z_room.c", 691);
}

typedef struct
{
    char unk_00[0x0E];
    s16  unk_0E;
} struct_80041C10_ret;

extern struct_80041C10_ret* func_80041C10(CollisionContext*, s32, s32);

BgImage* func_80096A74(PolygonType1* polygon1, GlobalContext* globalCtx)
{
    Camera* camera;
    s32 camId;
    s16 camId2;
    Player* player;
    BgImage* bgImage;
    s32 i;

    camera = globalCtx->cameraCtx.activeCameraPtrs[globalCtx->cameraCtx.unk_5C0];
    camId = camera->unk_148;
    camId2 = func_80041C10(&globalCtx->colCtx, camId, 50)->unk_0E;
    if (camId2 >= 0)
        camId = camId2;

    player = (Player*)globalCtx->actorCtx.actorList[ACTORTYPE_PLAYER].first;
    player->actor.params = (player->actor.params & 0xFF00) | camId;

    bgImage = SEGMENTED_TO_VIRTUAL(polygon1->multi.list);
    for (i = 0; i < polygon1->multi.count; i++)
    {
        if (bgImage->id == camId)
            return bgImage;
        bgImage++;
    }

    // Translates to: "z_room.c: DATA CONSISTENT WITH CAMERA ID DOES NOT EXIST camid=%d"
    osSyncPrintf("\x1B[41;37mz_room.c:カメラＩＤに一致するデータが存在しません camid=%d\n\x1B[m", camId);
    func_80002E50("../z_room.c", 726);

    return NULL;
}

// Room Draw Polygon Type 1 - Multi Format
#ifdef NON_MATCHING
// regalloc differences
void func_80096B6C(GlobalContext* globalCtx, Room* room, u32 flags)
{
    Camera* camera;
    Gfx* spA8;
    BgImage* bgImage;
    PolygonType1* polygon1;
    PolygonDlist* polygonDlist;
    u32 sp98;
    u32 sp94;
    u32 sp90;
    u32 sp8C;
    GraphicsContext* gfxCtx;
    Gfx* gfxArr[4];

    gfxCtx = globalCtx->gfxCtx;
    func_800C6AC4(gfxArr, globalCtx->gfxCtx, "../z_room.c", 752);

    camera = globalCtx->cameraCtx.activeCameraPtrs[globalCtx->cameraCtx.unk_5C0];
    sp98 = (camera->unk_142 ^ 0x19) < 1U;
    polygon1 = &room->mesh->polygon1;
    polygonDlist = SEGMENTED_TO_VIRTUAL(polygon1->dlist);
    bgImage = func_80096A74(polygon1, globalCtx);
    sp94 = (flags & 1) && sp98 && bgImage->source && !(gGameInfo->unk_106 & 1);
    sp90 = (flags & 1) && polygonDlist->opa && !(gGameInfo->unk_106 & 2);
    sp8C = (flags & 2) && polygonDlist->xlu && !(gGameInfo->unk_106 & 4);

    if (sp90 || sp94)
    {
        gSPSegment(gfxCtx->polyOpa.p++, 0x03, room->segment);

        if (sp90)
        {
            func_80093D18(globalCtx->gfxCtx);
            gSPMatrix(gfxCtx->polyOpa.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(gfxCtx->polyOpa.p++, polygonDlist->opa);
        }

        if (sp94)
        {
            // gSPLoadUcodeL(gfxCtx->polyOpa.p++, rspS2DEX)?
            gSPLoadUcodeEx(gfxCtx->polyOpa.p++, D_00113070, D_001579A0, 0x800);

            if (1)
            {
                Vec3f sp5C;
                spA8 = gfxCtx->polyOpa.p;
                func_8005AFB4(&sp5C, camera);
                func_8009638C(&spA8, bgImage->source, bgImage->tlut,
                              bgImage->width, bgImage->height,
                              bgImage->fmt, bgImage->siz,
                              bgImage->mode0, bgImage->tlutCount,
                              (sp5C.x + sp5C.z) * 1.2f + sp5C.y * 0.6f,
                              sp5C.y * 2.4f + (sp5C.x + sp5C.z) * 0.3f);
                gfxCtx->polyOpa.p = spA8;
            }

            // gSPLoadUcode(gfxCtx->polyOpa.p++, func_800D2E14(), func_800D2E20())?
            gSPLoadUcodeEx(gfxCtx->polyOpa.p++, func_800D2E14(), func_800D2E20(), 0x800);
        }
    }

    if (sp8C)
    {
        gSPSegment(gfxCtx->polyXlu.p++, 0x03, room->segment);
        func_80093D84(globalCtx->gfxCtx);
        gSPMatrix(gfxCtx->polyXlu.p++, &D_8012DB20, G_MTX_MODELVIEW | G_MTX_LOAD);
        gSPDisplayList(gfxCtx->polyXlu.p++, polygonDlist->xlu);
    }

    func_800C6B54(gfxArr, globalCtx->gfxCtx, "../z_room.c", 819);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_80096B6C.s")
#endif

// Room Draw Polygon Type 1
void func_80096F6C(GlobalContext* globalCtx, Room* room, u32 flags)
{
    PolygonType1* polygon1 = &room->mesh->polygon1;

    if (polygon1->format == 1)
        func_80096680(globalCtx, room, flags);
    else if (polygon1->format == 2)
        func_80096B6C(globalCtx, room, flags);
    else
        func_80002E50("../z_room.c", 841);
}

void func_80096FD4(GlobalContext* globalCtx, Room* room)
{
    room->num = -1;
    room->segment = NULL;
}

#ifdef NON_MATCHING
// regalloc differences
u32 func_80096FE8(GlobalContext* globalCtx, RoomContext* roomCtx)
{
    RomFile* roomList;
    TransitionActorEntry* transitionActor;
    s32 i, j;
    s8 frontRoom;
    s8 backRoom;
    u32 roomSize;
    u32 maxRoomSize;
    u32 frontRoomSize;
    u32 backRoomSize;
    u32 cumulRoomSize;
    u8 nextRoomNum;

    maxRoomSize = 0;
    roomList = globalCtx->roomList;
    for (i = 0; i < globalCtx->nbRooms; i++)
    {
        roomSize = roomList[i].vromEnd - roomList[i].vromStart;
        osSyncPrintf("ROOM%d size=%d\n", i, roomSize);
        if (maxRoomSize < roomSize)
            maxRoomSize = roomSize;
    }

    if (globalCtx->nbTransitionActors != 0)
    {
        j = 0;
        roomList = globalCtx->roomList;
        transitionActor = &globalCtx->transitionActorList[0];
        SyncPrintfWithThreadId("../z_room.c", 912);
        osSyncPrintf("game_play->room_rom_address.num = %d\n", globalCtx->nbRooms);
        for (j = 0; j < globalCtx->nbTransitionActors; j++)
        {
            frontRoom = transitionActor->frontRoom;
            backRoom = transitionActor->backRoom;
            frontRoomSize = (frontRoom < 0) ? 0 : roomList[frontRoom].vromEnd - roomList[frontRoom].vromStart;
            backRoomSize = (backRoom < 0) ? 0 : roomList[backRoom].vromEnd - roomList[backRoom].vromStart;
            cumulRoomSize = (frontRoom != backRoom) ? frontRoomSize + backRoomSize : frontRoomSize;
            osSyncPrintf("DOOR%d=<%d> ROOM1=<%d, %d> ROOM2=<%d, %d>\n",
                         j, cumulRoomSize, frontRoom, frontRoomSize, backRoom, backRoomSize);
            if (maxRoomSize < cumulRoomSize)
                maxRoomSize = cumulRoomSize;
            transitionActor++;
        }
    }

    osSyncPrintf("\x1B[33m");
    // Translates to: "ROOM BUFFER SIZE=%08x(%5.1fK)"
    osSyncPrintf("部屋バッファサイズ=%08x(%5.1fK)\n", maxRoomSize, (f64)(maxRoomSize * 0.0009765625f));
    roomCtx->bufPtrs[0] = Game_Alloc(globalCtx, maxRoomSize, "../z_room.c", 946);
    // Translates to: "ROOM BUFFER INITIAL POINTER=%08x"
    osSyncPrintf("部屋バッファ開始ポインタ=%08x\n", roomCtx->bufPtrs[0]);
    roomCtx->bufPtrs[1] = (void*)((s32)roomCtx->bufPtrs[0] + maxRoomSize);
    // Translates to: "ROOM BUFFER END POINTER=%08x"
    osSyncPrintf("部屋バッファ終了ポインタ=%08x\n", roomCtx->bufPtrs[1]);
    osSyncPrintf("\x1B[m");
    roomCtx->unk_30 = 0;
    roomCtx->status = 0;

    if (gSaveContext.respawn_flag > 0)
        nextRoomNum = gSaveContext.respawn[gSaveContext.respawn_flag-1].room_index;
    else
        nextRoomNum = globalCtx->setupEntranceList[globalCtx->curSpawn].room;
    func_8009728C(globalCtx, roomCtx, nextRoomNum);

    return maxRoomSize;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_room/func_80096FE8.s")
#endif

s32 func_8009728C(GlobalContext* globalCtx, RoomContext* roomCtx, s32 roomNum)
{
    u32 size;

    if (0) ; // Necessary to match

    if (roomCtx->status == 0)
    {
        roomCtx->prevRoom = roomCtx->curRoom;
        roomCtx->curRoom.num = roomNum;
        roomCtx->curRoom.segment = NULL;
        roomCtx->status = 1;

        if (roomNum >= globalCtx->nbRooms)
            __assert("read_room_ID < game_play->room_rom_address.num", "../z_room.c", 1009);

        size = globalCtx->roomList[roomNum].vromEnd - globalCtx->roomList[roomNum].vromStart;
        roomCtx->unk_34 = (void*)ALIGN16((s32)roomCtx->bufPtrs[roomCtx->unk_30] - ((size + 8) * roomCtx->unk_30 + 7));

        if (0) ; // Also necessary to match

        osCreateMesgQueue(&roomCtx->loadQueue, &roomCtx->loadMsg, 1);
        func_80001A5C(&roomCtx->getfile, roomCtx->unk_34, globalCtx->roomList[roomNum].vromStart, size,
                      0, &roomCtx->loadQueue, 0, "../z_room.c", 1036);
        roomCtx->unk_30 ^= 1;

        return 1;
    }

    return 0;
}

s32 func_800973FC(GlobalContext* globalCtx, RoomContext* roomCtx)
{
    if (roomCtx->status == 1)
    {
        if (!osRecvMesg(&roomCtx->loadQueue, NULL, OS_MESG_NOBLOCK))
        {
            roomCtx->status = 0;
            roomCtx->curRoom.segment = roomCtx->unk_34;
            D_80166FB4 = PHYSICAL_TO_VIRTUAL2(roomCtx->unk_34);

            Scene_ExecuteCommands(globalCtx, roomCtx->curRoom.segment);
            func_8008E750(globalCtx, (Player*)globalCtx->actorCtx.actorList[ACTORTYPE_PLAYER].first);
            Actor_SpawnTransitionActors(globalCtx, &globalCtx->actorCtx);

            return 1;
        }

        return 0;
    }

    return 1;
}

void Room_Draw(GlobalContext* globalCtx, Room* room, u32 flags)
{
    if (room->segment != NULL)
    {
        D_80166FB4 = PHYSICAL_TO_VIRTUAL(room->segment);
        if (room->mesh->polygon.type >= ARRAY_COUNTU(sRoomDrawHandlers))
            __assert("this->ground_shape->polygon.type < number(Room_Draw_Proc)", "../z_room.c", 1125);
        sRoomDrawHandlers[room->mesh->polygon.type](globalCtx, room, flags);
    }
}

void func_80097534(GlobalContext* globalCtx, RoomContext* roomCtx)
{
    roomCtx->prevRoom.num = -1;
    roomCtx->prevRoom.segment = NULL;
    func_80031B14(globalCtx, &globalCtx->actorCtx);
    Actor_SpawnTransitionActors(globalCtx, &globalCtx->actorCtx);
    func_80080E04(globalCtx, roomCtx->curRoom.num);
    if (!((globalCtx->sceneNum >= 0x51) && (globalCtx->sceneNum < 0x64)))
        func_800807A0(globalCtx);
    func_800F66C0(globalCtx->roomCtx.curRoom.echo);
}
