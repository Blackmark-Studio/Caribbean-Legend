// 任务《狡诈的克索奇坦岛》的NPC对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你有什么事吗? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 圣奎特里亚的骷髅船长
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "你... 还是... 得死。 他会来... 杀了你... 就像杀了我们所有人... 就像杀了这里的每个人... ";
			link.l1 = "什么? 你是谁? 你在说谁? ";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "他很高大... 刀枪不入... 他杀人... 他会杀了你。 我必须杀了你... 如果我杀了你, 你就不会变成我们这样... 你不明白... 你会死于他的剑下... 你会变成我们这样... 像圣奎特里亚上的所有人一样... ";
			link.l1 = "没门! ";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// 库库尔坎面具守卫
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "我等你很久了! ..";
			link.l1 = "呃! .. 太惊人了! .. 真是具骷髅! ";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "我看到了... 我感觉到了... 你给我带来了... 自由... ";
			link.l1 = "你在说什么? 你是什么东西? ! ";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "我是克索奇坦的守护者, 库库尔坎面具的看守者... 也是你注定的死亡! ..";
			link.l1 = "... ";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "停下... ";
			link.l1 = "我为什么要停下? 你喘不过气了吗, 骨头架子? ";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "不。 你永远杀不了我。 即使有那把魔法匕首也不行。 我们的决斗可能会持续很久很久, 直到你耗尽体力死去。 ";
			link.l1 = "是吗? 那你为什么不攻击我? ";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "你是个勇敢强大的战士, 还持有酋长之爪。 我必须让你活下去, 因为持有这把匕首。 敢与我战斗的人, 理应得到他所求之物。 ";
			link.l1 = "你是谁? 守护者, 你究竟是谁? ";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "他们曾叫我阿尔贝托.卡斯柯。 我是阿隆索.德.马尔多纳多小队的士兵。 我们找到了古老的塔亚萨尔, 但他们抓住了我们并把我们献祭了。 因为我的身高和力量, 异教祭司卡内克把我变成了克索奇坦的守护者, 库库尔坎面具的看守者。 每个踏上克索奇坦的人都被我找到并亲手杀死, 然后变成不死族。 酋长之爪匕首被用来在我身上刻下这里的地图。 我将永远守护面具, 不得安宁, 直到我手中握着这把匕首。 ";
			link.l1 = "你需要酋长之爪? ";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "是的。 既然你需要面具。 把匕首给我。 我会找到期待已久的安宁, 你会得到面具。 我发誓你能带着它活着离开克索奇坦。 ";
			link.l1 = "我接受你的提议, 守护者。 我在洗礼池喷泉后面的基座上看到了面具。 是那个吗? ";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "是的。 这是库库尔坎本人的强大神器, 飞蛇之神。 我们谈完后, 你可以走过去拿走它。 ";
			link.l1 = "希望你信守诺言, 守护者... ";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "我发过誓... ";
			link.l1 = "那拿着酋长之爪吧。 希望它能让你的灵魂得到安宁。 ";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("你已交出酋长之爪");
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			dialog.text = "哦, 我等这一刻等了多久! 现在我终于可以离开了... 但作为告别礼物, 我想把我的一部分力量传给你。 这将是阿尔贝托.卡斯柯最后的礼物。 ";
			link.l1 = "... ";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "现在我该走了。 别磨蹭, 没有守护者和库库尔坎面具, 这座岛很快就会永远消失。 ";
			link.l1 = "没什么可遗憾的。 世界上少了个鬼地方... 但等等, 守护者! 你去过塔亚萨尔! 请告诉我那是什么地方。 ";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "那是座古老的玛雅城市。 它的外观保留了人们居住时的样子。 宏伟的神庙, 高耸的金字塔... 现在, 伊察部落住在那里, 声称是玛雅人的直系后裔。 他们试图在宗教。 文化和生活方式上全面模仿祖先。 ";
			link.l1 = "我怎么去那里? ";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "我们的指挥官知道路, 阿隆索.德.马尔多纳多。 我们只是跟着他穿过丛林。 我只记得我们在珍珠角以北的蚊子湾登陆, 然后向西深入丛林。 ";
			link.l1 = "塔亚萨尔有什么值得注意的? ";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "那里处处都值得注意。 绝对是这样。 但我们只对玛雅宝藏感兴趣。 我们找到了它们。 我们为此付出了沉重代价, 尤其是我。 但现在, 我终于自由了! ";
			link.l1 = "去塔亚萨尔之前我需要知道什么? ";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "伊察人拥有强大的力量和智慧。 他们憎恨任何国籍的白人, 会摧毁任何入侵他们领土的外来者。 普通伊察战士不会进行任何交流, 但卡内克或他的儿子乌拉坎, 如果他们看到面具... 可能会。 如果你能活着到达塔亚萨尔, 你自己会看到的。 但你能离开那里吗... ";
			link.l1 = "卡内克会把所有到塔亚萨尔的白人都献祭吗? ";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "我想是的。 但可能不包括佩戴库库尔坎面具的人。 ";
			link.l1 = "好吧。 我会指望这一点。 ";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "再见, 士兵。 希望你将面具的力量用于正途。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}