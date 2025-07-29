// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想干什么? ";
			link.l1 = "没什么。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "你想干啥, 白脸? Tichingitu没啥要跟你说的。";
			link.l1 = "你的名字叫Tichingitu? 嗯。听着, 战士, 俺不是来这儿盯着你看的。俺来是想问你一句: 你为啥闯进那个胖子的屋子? ";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "怎么不说话? 不聪明啊。你会因为偷窃和其他罪行被吊死。告诉我你为什么要这么做, 也许我还能帮你一把。";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu走了许多许多路, 穿过大海, 从茂密的森林和沼泽来到白人的城镇。Tichingitu累了, 想吃东西。Tichingitu快要饿死了。没人愿意帮Tichingitu。他们大喊: “滚开, 红皮狗。”酒馆老板像赶癞皮狗一样把印第安人赶了出去。Tichingitu只想吃点东西。";
			link.l1 = "该死, 你怎么会从……你那片森林跑到这镇上来的? ";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu被部落赶出来了。Tichingitu和部落的萨满打了一架, 萨满去告诉酋长, 还对Tichingitu下了诅咒, Tichingitu只好离开部落, 远远地离开了自己的土地。Tichingitu现在没家、没武器, 啥都没有。";
			link.l1 = "这可真是倒霉啊。你怎么会和自己人打起来了? ";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "部落的萨满是个恶人。他说有邪灵附身在我妻子身上, 妻子必须死。可我妻子只是生病了, 根本没有什么邪灵。Tichingitu给我妻子治病, 萨满却要杀了她。Tichingitu反对萨满, 大家又都反对Tichingitu, 最后Tichingitu只好离开。";
			link.l1 = "你是为了救你老婆? 所以才被村子赶出来的? ";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "是的, 白脸。Tichingitu没得选, 不是偷就是饿死……";
			link.l1 = "唉, 我说啊……一个饿肚子的可怜人偷了点零钱, 就要上绞刑架……Tichingitu, 俺会尽力帮你的。俺认识Fadey, 就是你溜进他家的那个壮汉。也许俺能想点办法……俺这就去找指挥官谈谈。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu等着。印第安人不怕死。萨满诅咒了Tichingitu, Tichingitu必须死。";
			link.l1 = "还没到山穷水尽的地步。我会尽力帮忙……";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu等着。印第安人不怕死。萨满诅咒了Tichingitu, Tichingitu必须死。";
			link.l1 = "无需灰心。你的囚禁已经结束了。是我帮你获得了自由。";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "白脸的笑话? Tichingitu自由了吗? ";
			link.l1 = "不, 我不是在开玩笑。他们马上就要打开你的牢房, 把你放出来。跟我走, 我带你离开这监狱。";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "你自由了, 快走吧, Tichingitu, 记住别再偷东西, 也别再惹麻烦! 最好找个印第安村子, 跟你自己人一起生活, 我觉得他们不会拒绝你的。";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu不走。主人救了Tichingitu的命。Tichingitu留下。Tichingitu的命是主人的。";
			link.l1 = "嗯? 你在说什么? 什么主人, 什么命运? 你听不懂老子的话吗? 你自由了! 快走! ";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "印第安人欠债, 白人主人。Tichingitu会忠心侍奉您, 绝不欺骗。Tichingitu会打仗。Tichingitu愿为主人战死。他会留下。";
			link.l1 = "天啊! 该死……Tichingitu, 我算什么主子啊? 我帮你可不是为了让你当奴隶。";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu不是奴隶。Tichingitu是自由的印第安人。Tichingitu愿意为你效劳。Tichingitu会打仗, 任何狗敢靠近主人都得死。Tichingitu会清理和装填火枪。Tichingitu也会开枪。";
			link.l1 = "不过……你知道吗, Tichingitu, 这主意倒也不错。老子正缺几个忠心的人, 你看起来也不坏, 还会用火枪。再说你一个人能干啥? 到头来还不是又去偷东西, 下回肯定就得上绞刑架了……行吧, 你可以留下。但记住, 跟着老子可没安生日子过。";
			link.l1.go = "Tichingitu_13";
			link.l2 = "好了, 够了。带着平安离开吧, 红皮肤的兄弟。愿你的神明保佑你! ";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu什么都不怕, 白人主人。Tichingitu很高兴为您效劳。Tichingitu会忠诚到底, 直到最后一口气。";
			link.l1 = "好吧。欢迎加入船员, Tichingitu! ";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Cocoa";
			sld.lastname = "Leaf";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu听你吩咐, "+pchar.name+"船长! ";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, 我马上要前往一个叫Tayasal的印第安老村庄。老实说, 这趟旅程极其危险, 也非常离奇—要通过一个传送神像。你……你愿意和我一起去吗? ";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, 把船上的情况都详细汇报一遍。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "每次我们靠岸时, 我都要你去采购一些特定的货物。";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "听我号令! ";
            Link.l1.go = "stay_follow";
			link.l2 = "目前没什么事。放松点! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "船只报告? Tichingitu没有什么报告, 主人。只有武器和衣服。Tichingitu哪儿都没拿到什么报告。";
			Link.l1 = "行吧, 随你。";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "主人, Tichingitu从不在没有您的情况下踏进殖民地。Tichingitu一进商店, 所有人都觉得Tichingitu又是小偷。然后就进监狱了。";
			link.l1 = "嗯, 你说得大概没错。可别又提坐牢那事了。再说了, 谁会信你是管账的啊。";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "你有什么吩咐? ";
            Link.l1 = "站住! ";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "跟上我, 别掉队! ";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "你需要更换你的火器弹药类型。";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "更换你的火枪弹药类型。";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "更换你的主战武器。";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "我要你和目标保持距离。";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "战斗开始时你将使用: ";
			Link.l1 = "刀";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "火枪";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "计划有变! ";
            Link.l1 = "请放松。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "计划有变! ";
            Link.l1 = "请放轻松。";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "还有多远, 船长? 告诉Tichingitu还有多少码, 但别超过二十。";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "船长, 恕Tichingitu直言, 俺听不懂你说啥。";
				link.l1 = "抱歉, 是我搞错了……";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu站着不动, 一点反应都没有。这就是你想要的, 船长? ";
				link.l1 = "正是如此。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu离目标超过二十码就不行了。那他就会失手。";
				link.l1 = "好吧, 保持二十码的距离。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu全都明白。Tichingitu会按你说的去做。";
			link.l1 = "很好。";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingitu的命早就和俺船长绑在一块儿了。印第安人不会忘记船长为Tichingitu做过的事。船长让Tichingitu去哪儿, Tichingitu就去哪儿, 绝不多问, 绝不迟疑。";
			link.l1 = "谢谢你, 我的朋友! ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "我们什么时候出发? ";
			link.l1 = "稍后再说。现在我们得为旅途做准备。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "咱们给白人一百枚达布隆, 离开, 然后自由地完成咱们的活儿。";
			link.l1 = "要是咱们又被逮住了咋办? ";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "我们付一千达布隆。";
			link.l1 = "玩世不恭, 却极为敏锐。";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "瓜德罗普更糟。";
			link.l1 = "怎么说? ";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "那边, 他们只想吊死Tichingitu一个。这里, 可不止一个要上绞刑架。还不算太糟嘛。";
			link.l1 = "这也太讽刺了吧! ";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "近距离开枪。船长, 这老头挺硬朗的, 要是动作快点还能救他。";
			link.l1 = "……";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "白人从不懂怜悯, 船长, 俺的族人死了好多, 太多了。但你们死得更多。";
			link.l1 = "他们是你们部落的人吗? ";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "“有……有些是俺的。”";
			link.l1 = "撑住, 伙计。";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "还要再加一百金币? ";
			link.l1 = "嗯? 你是问我是不是又要为Deluc的保释金买单? ";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "是的。";
			link.l1 = "我自己也不确定……你怎么看? ";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "我们得把他保释出来。";
			link.l1 = "这很光荣啊。永远不抛下自己人, 是吧? ";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "或者就扔下他。让弱者在丛林里被美洲虎吃掉。";
			link.l1 = "谁? ";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "大猫。";
			link.l1 = "Tichingitu, 我实在听不懂你在说什么。你就直接告诉我, 这种情况下我该怎么办? ";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "用你自己的脑子。";
			link.l1 = "非常有用! ";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			Return_TichingituOfficer();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
