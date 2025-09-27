void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "您需要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "欢迎来到寒舍, 先生们。 有什么可以为您效劳? ";
			link.l1 = "勒瓦瑟向您问好, 先生。 ";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "原来如此... 艾丽西亚! 请离开我们。 这些先生们找我有事。 ";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "但是... ";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "我爱你, 亲爱的。 那就去吧! ";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "奇妙的安排, 主啊! 在世界尽头找到一生挚爱, 就算失去一切也值得! 先生们, 我听候差遣。 我们能做个交易吗? ";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "不行, 也别想乞求怜悯。 ";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "骑士团骑士不该乞求怜悯。 ";
			link.l1 = "不过是前骑士罢了。 ";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "就算把所有墨水都用完, 官僚也无法剥夺我的头衔。 ";
			link.l1 = "既然如此, 证明给我看。 但首先满足我的好奇心: 你是王室的叛徒吗? 否则我无法理解为何勒瓦瑟如此想置你于死地。 ";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "我忠于誓言, 先生, 请勿质疑。 我只能说, 有个王室叛徒派我来铲除另一个叛徒。 他会不断派更有能力的兄弟来, 直到成功为止。 废话少说, 先生们, 拔剑吧! ";
			link.l1 = "... ";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "啊哈! 谢了, 船长。 这家伙真难对付, 我自己肯定打不过。 ";
			link.l1 = "不知为何, 这场胜利让我高兴不起来。 我们该结束了吧? ";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "还没, 首先得清理现场, 把刚才飞快逃到二楼的女孩解决掉。 ";
			link.l1 = "什么? ! 住手! 你疯了吗, 克劳德? 我不是屠夫! ";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "你不必动手, 船长。 再说这都怪你: 不该在她面前提勒瓦瑟。 ";
			link.l1 = "胡说八道, 你心里清楚。 如果你再敢胡言乱语, 后果自负。 ";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "嘿! 是我错了, 船长。 确实, 勒瓦瑟的命令明确要求不仅要除掉骑士, 还要解决他的所有同伴。 所有人, 明白吗? 这些人不好惹, 必须认真对待他们的要求。 别妨碍我工作, 船长。 最后一次脏活, 之后我发誓永远追随你! ";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("声望检查通过", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(值得信赖) (荣誉) 你曾说我注定飞黄腾达, 还乐意助我一臂之力。 ";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("声望过低! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("特质检查失败", "Trustworthy");
			}
			link.l2 = "去你的! 干你的脏活吧。 我接受你的誓言, 你最好当真。 明白吗? ";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "这个代价我付不起, 克劳德。 我不会让你杀那个女孩。 ";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "嘿! 看来我们命中注定要互相残杀, 嗯, 船长? ";
			link.l1 = "看来是。 我们从托尔图加未竟之处继续吧? ";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "办妥了, 船长。 那女孩真让我吃惊... ";
			link.l1 = "我不想听。 我信守了承诺, 现在轮到你了。 ";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "黄金是一回事, 但为一个雇佣兵冒险则更有价值。 我永远追随你, 船长。 ";
			link.l1 = "既然如此, 我们结束吧。 ";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "是, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//克劳德.迪朗成为常驻军官
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "我说过。 你想说什么, 船长? ";
			link.l1 = "证明你不是随口说说。 你想在我船上谋个职位? 未来战利品的分成? 那就听我命令。 别碰那女孩。 为什么? 因为如果你动手, 就永远是个屠夫, 而我船上容不下这种人。 ";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "这是我们第二次差点拼个你死我活, 船长\n又一次, 你靠三寸不烂之舌赢了! 哈哈! 你说得对! 去他的女孩。 反正我就是个禽兽。 允许我加入船员吗? ";
			link.l1 = "欢迎, 克劳德。 这次是真心的。 ";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
            LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			
			sld = CharacterFromID("Duran");	//克劳德.迪朗成为常驻军官
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "出了点事, 船长。 ";
			Link.l1 = "让我猜猜: 你又要威胁辞职要求加薪了? ";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "嘿! 这次不是... 别担心, 船长, 只要你付钱, 我就是你的... 当然是在合理范围内。 这是我们雇佣兵的生存之道。 就算是最优秀的雇佣兵也只能拿微薄薪水。 ";
			link.l1 = "我们直接说正事吧? ";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "还记得托尔图加那个婊子吗? ";
			link.l1 = "马塞利娜? 总督的妻子? 那种女人谁也忘不了。 ";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "我来勒瓦瑟家不是偶然。 我和那个恶棍异教徒有过交易。 ";
			link.l1 = "你如此贬低权贵, 真让人意外, 克劳德。 ";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "嗯? 嘿! 勒瓦瑟就是魔鬼! 他比靠他生存的海盗还坏! ";
			link.l1 = "你自己刚说和他有交易。 这不是有点虚伪吗? ";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "我不是天使, 船长, 我靠杀人谋生。 这也是你看重我的原因, 不是吗? 但就算是我这种人, 听到托尔图加勒瓦瑟老巢里对女人的所作所为, 也会不寒而栗! ";
			link.l1 = "我对谣言没兴趣。 此人是贵族, 国王的仆人, 理应受到尊重。 ";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "所以你抢了这位国王仆人的东西, 还睡了他老婆? 嘿! 随你便, 船长。 我们开门见山吧。 大人命令我找到并杀死一个人。 任务很常规, 只是很少来自如此高位, 而且是亲自下令。 ";
			link.l1 = "你想怎样? 放你走以便信守承诺杀了那人? ";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "我想让你帮我完成任务, 船长。 我在托尔图加走投无路时同意加入你的船队, 但不完成任务我寝食难安。 勒瓦瑟发现了会杀了我。 再说, 任务没完成也不专业。 ";
			link.l1 = "和客户的妻子有染算专业吗? 特别是考虑到我们对话的开头, 你精准描述了我们之间的关系 —血债换金钱, 嗯? ";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "如果你帮我, 得到的不仅是我的剑, 还有我的忠诚。 我一眼就看出你注定飞黄腾达, 船长。 我很乐意助你一臂之力。 ";
			link.l1 = "我承认, 有你这样的人才保护我会更安全。 去哪里找你的目标? ";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "目前你的剑就够了。 我不是刺客。 稍息, 军官! ";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "是, 船长。 问问也无妨。 ";
			link.l1 = "... ";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			ReturnOfficer_Duran();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "嘿! 问题就在这, 船长。 我只知道他是个逃亡的前马耳他骑士团骑士, 躲在英国领土某处。 此人出身高贵, 不会住在茅屋里。 ";
			link.l1 = "骑士团骑士? ";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "前骑士。 是的, 我已经后悔接这个任务一千次了。 骑士打起仗来像魔鬼, 我保证这会是对你剑术的严峻考验。 ";
			link.l1 = "我不喜欢, 但可以试试。 那么: 此人不穷, 是贵族, 躲在英国人那里? 勒瓦瑟没说为什么要除掉他? ";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "他当然不会说! 但这显然是政治原因, 否则会派士兵来。 ";
			link.l1 = "我试试, 但不能保证。 ";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "谢了, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			ReturnOfficer_Duran();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
}