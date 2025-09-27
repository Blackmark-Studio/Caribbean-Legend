
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// 格里芬多 -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("", "一位女性... 还是船长! 如今真是无奇不有。 小姐, 您光彩照人。 可惜您的美貌给法兰西王室带来了如此多的哀愁\n") + "庞斯所有的命令最终都是这样的结局: 一个进了监狱, 另一个 —要么步他后尘, 要么今日会战死沙场。 ";
			link.l1 = "您显然不该出现在这里。 为何派如此杰出的军官和精良的船只来做赏金猎人的脏活? ";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "命令不是用来讨论的, 是用来执行的。 如果每个船长都只选择值得执行的命令 —我们就不会有海军了。 ";
			link.l1 = "跟您的手下说去。 ";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "您把我逼入绝境, 试图动摇我的忠诚和誓言。 鉴于当前处境, 这手段未免卑劣。 让我们用剑刃对决来结束这场纷争, 而非唇枪舌战! ";
			link.l1 = "(领导力) 还有第三条路。 停止做有失军官身份的脏活, 加入我 —我将向您展示一个不同的世界。 ";
			link.l1.go = "FraOff_HireCheck";
			link.l2 = "那就拔剑吧! ";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
				notification("技能检查失败 (80)", SKILL_LEADERSHIP);
				dialog.text = "叛徒在任何地方都不会有好下场, 而我不会成为叛徒。 接招吧! ";
				link.l1 = "您错过了机会, 接招吧! ";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
			notification("技能检查通过", SKILL_LEADERSHIP);
			dialog.text = "我向王室宣誓效忠, 而非向那些派我们送死来掩盖自身失误的优越感, 古板的官僚。 但您 —您是我国王的敌人, 我不能无视这一点。 ";
			link.l1 = "明天我或许就能为对贵国犯下的罪孽赎罪 —只需贿赂合适的中间人。 这更多反映了您上级的问题, 而非我。 ";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "所言极是。 我已厌倦了容忍这一切。 如果您承诺不再与法国为敌, 我准备效忠于您。 ";
			link.l1 = "我不知我们将与谁狭路相逢, 也无法保证什么。 但我承诺会通情达理。 欢迎加入船队, " + NPChar.name+ "军官! "; // 他其实根本没说自己的名字
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// 艾尔.卡萨多尔 -->
		case "FireBrigade_spa":
			// to_do: 检查零值?
			dialog.text = "这就是头号公敌的样子。 希望您对这个头衔感到自豪, 海盗。 您必定为此付出了不少努力\n根据贸易署的记录, 您已摧毁了 " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " 艘悬挂西班牙王室旗帜的船只。 而今天, 我这艘漂亮的船也将加入该名单" + GetSexPhrase(".","\n西班牙舰队真可悲! 我们深受疾病。 偏袒和背叛之苦... 但竟被一个女人击败? ");
			link.l1 = "您是最后一个站着的人, 您的船员都死了。 您也一样, 只是还没意识到而已。 ";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "真遗憾, 阿尔巴没接到这个任务, 他会做得更好。 但我仍会尽力完成任务。 ";
			link.l1 = "您真是祖国的忠实儿子。 准备去见祖国的英雄们吧, 先生。 ";
            link.l1.go = "Alonso_2";
			link.l2 = "猎人变成了猎物。 您所有的慷慨陈词都毫无意义 —这是亘古不变的真理。 ";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "感谢您给我喘息的机会, 但现在该用剑说话了。 ";
			link.l1 = "拔剑吧! ";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "感谢您给我喘息的机会, 但现在该用剑说话了。 ";
			link.l1 = "准备受死吧! ";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            MakeUnpushable(NPChar, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// 奇美拉 -->
        case "FireBrigade_eng":
			// to_do: 你-您在艾伦
			dialog.text = GetSexPhrase(PChar.Name+ "! 您的名字在报告中频频出现, 我感觉我们好像早就认识", "麦克阿瑟小姐! 您的赞助人知道您在做什么吗? 啊, 没关系, 我相信他很快就会成为我的下一个目标") + "\n您很幸运: 我的上司喜欢发送与上一条矛盾的紧急命令。 如果我不是在忙着清理安提瓜的旧部... 算了, 够了, 您让我无法专注于正事。 ";
			link.l1 = "您也让我分心了。 ";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
			dialog.text = "后舷被链弹击中, 我差点就错过了! 如果我这把老骨头动作再快一点, 就会亲自把那混蛋送进海魔的口中。 谢谢, 船长。 也替我已故的赞助人感谢您! ";
			link.l1 = "您是谁? 囚犯吗? 是我的船员救了您? ";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
			dialog.text = "本人查理.克尼佩尔, 英国海军最优秀的炮手! ";
			link.l1 = "考特尼说他追踪您很久了。 这其中有什么故事? ";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
			dialog.text = "多年来, 我为一位名叫理查德.弗利特伍德的勇敢英国船长效力。 我们一起经历了许多战役, 投身于我们真正热爱的事业 —英国海军。 但有一天, 一切都变了\n伦敦的高层把我们当作棋子, 我们攻击自己人, 为他人收拾烂摊子而玷污了制服。 现在轮到我们了... ";
			link.l1 = "我不做评判。 生活很复杂, 尤其是当您身不由己时。 ";
			link.l1.go = "Kneepel_2_good";
			link.l2 = "那么, 您是说过去的罪孽最终还是找上了您? ";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
			dialog.text = "我不后悔为国家效力, 只是... 这很伤人, 船长。 尤其是对我的赞助人和他可怜的妻子。 ";
			link.l1 = "现在打算怎么办? ";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
			dialog.text = "不必冷嘲热讽... 我们已经为自己的罪孽付出了惨重代价! ";
			link.l1 = "现在打算怎么办? ";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
			dialog.text = "现在我是一个没有名字。 没有祖国的人。 我可以去任何地方, 但眼下无处可去, 也无人可伴。 各地都需要炮手, 但并非每艘船都有加农炮。 ";
			link.l1 = "加入我吧。 我与英国舰队的关系算不上融洽, 但我尊重其中的精英。 ";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
			link.l2 = "我有加农炮。 如果您真有那么优秀, 我的船队永远有真正专业人士的一席之地。 ";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
			dialog.text = "祖国等着绞死我, 西班牙和荷兰也是, 我还不喜欢法国人。 但您, 似乎需要一位优秀的炮手。 我加入, 船长。 一有机会我就去船舱, 有空过来喝一杯聊聊天。 ";
			link.l1 = "欢迎登船。 ";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
			dialog.text = "没门。 我宁愿强征一艘船, 消失在群岛最深的洞穴里。 感谢您的营救, 船长, 再见。 ";
			link.l1 = "... ";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
			NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // 文物
            NPChar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// 梅菲恩 -->
        case "FireBrigade_hol":
			dialog.text = "本不该是您走到这一步。 梅菲恩是公司的尖牙, 我的中队是复仇之剑。 您两者都摧毁了。 这... 不应该发生。 ";
			link.l1 = "他们像猎杀野兽一样派您来追我。 而我像困兽一样战斗 —当面临非战即死的局面时, 头脑会变得清醒。 最终只剩下一个问题: 我能否登上传奇双桅帆船的船舱 —无论生死。 ";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "奇怪 —看到一位女性指挥者, 这也不常见。 ") + "您在等我吗? ";
			link.l1 = "是的。 梅菲恩是一艘有历史的船。 与荷兰人交恶后, 我就知道他们迟早会派您来追我。 本可能是个体面的结局... 但看看现在的情况。 ";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "知己知彼, 百战不殆。 所以, 您做出了选择, 以自己的方式面对我的中队。 您已做好牺牲的准备, 却赢了。 现在我的性命在您手中, 为何不杀了我? ";
			link.l1 = "(领导力) 因为我认为, 仅为公司的野心就除掉一位传奇船长毫无意义。 我也曾身处您的境地 —作为棋子, 为他人利益服务, 听从他人命令。 我为您提供我曾经的选择: 自由。 ";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
			link.l2 = "因为每个船长都应拥有最后的话语权。 接招吧! ";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
			notification("技能检查失败 (50)", SKILL_LEADERSHIP);
			dialog.text = "自由不是别人给予的, 而是自己争取的。 并非所有谈论选择的人都能提供选择。 有些道路无法避免, 有些命令必须完成。 我的道路就在这里, 我的命令是坚持到底。 ";
			link.l1 = "所以您选择死亡? ";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "不, 我选择做自己。 ";
			link.l1 = "那就一战吧! ";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
			notification("技能检查通过", SKILL_LEADERSHIP);
			dialog.text = "您和罗登堡不同, 他视我为工具, 而您视我为平等的人。 牺牲并非美德, 我准备听听您的条件。 ";
			link.l1 = "很简单: 做我旗舰的领航员。 或者, 如果您愿意, 我会给您一艘属于自己的船, 让您打着我的旗号航行。 您不必再为公司收拾烂摊子, 或为他们掩盖丑事。 我自由了 —也向您提供与我一起自由的机会。 ";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "我见过很多: 鲜血。 黄金。 背叛。 公司会付钱 —但不会尊重; 会给船 —但会锁住您。 而您... 给了我选择。 如果您信守承诺 —朗威将不再是为他人意志效力的猎手, 而将成为一个真正的人, 一位船长, 或者 —站在一位知道航向的船长身边。 ";
			link.l1 = "欢迎加入船队, 朗威领航员。 ";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
            sld = GetCharacter(NPC_GenerateCharacter("Longway_FP", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = StringFromKey("QuestsUtilite_42");
			sld.lastname = StringFromKey("QuestsUtilite_43");
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.currentnode = "Longway_officer";
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
		
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
            sTemp = GetGeneratedItem("blade_41");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
            sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
            if(sTemp != "")
            {
                GiveItem2Character(sld,   sTemp);
                EquipCharacterbyItem(sld, sTemp);
                sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
                LAi_SetCharacterBulletType(sld, sTemp);
                LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
                sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
                if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
            }
			TakeNItems(sld, "potion2", 1);
            sld.quest.meeting = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*200; // 文物
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP    = 60.0;
			sld.Health.maxHP = 60.0;
            sld.CanTakeMushket = true;
			SetCharacterPerk(sld, "ShipEscape");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

            NPChar.lifeday = 0;
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

            AddDialogExitQuest("pchar_back_to_player");
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;
	}
}

// 待办事项
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
	sld.quest.OfficerPrice = sti(PChar.rank)*200; // 文物
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}