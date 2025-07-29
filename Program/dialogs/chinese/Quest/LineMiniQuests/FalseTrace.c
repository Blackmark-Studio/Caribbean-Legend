void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "程序错误, 请告知我们。 ";
			link.l1 = "好的! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "下午好, 船长... 嗯... 咳咳! 该死的矿场... 让我自我介绍一下。 我是亚当.雷纳。 我是个直爽人, 不喜欢拐弯抹角, 所以我就直说了。 你想赚大钱吗? 我给你提供一个小生意, 我们俩单靠自己都做不来。 ";
			link.l1 = "呵! 大钱? 有意思。 我听着呢, 亚当。 ";
			link.l1.go = "FalseTrace_1";
			link.l2 = "你知道吗, 抱歉, 但你看起来不太可靠。 所以我不会和你做任何生意。 ";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "可靠? 哈哈! 人不可貌相。 好吧, 没关系。 你刚刚错过了一个轻松快速赚大钱的好机会。 我会找个更合作的人... ";
			link.l1 = "我们的谈话结束了, 先生。 再见! ";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//选择目标点
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "哈! 很高兴和你这样思维敏捷的船长做生意。 那么, 任务很简单: 有一艘装满大量白银的快速帆船, 很快就会从当地某个港口起航。 单船, 没有护航。 很傻, 对吧? 咳咳\n易如反掌。 我告诉你在哪里和什么时候, 你拿下战利品, 我拿我的分成。 ";
			link.l1 = "当然, 你想现在就拿到现金? ";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "船长, 我看起来像个可怜的骗子吗? 没门。 我会和你一起参加这次突袭, 我们一起干。 战斗时我不会躲在货舱里, 恰恰相反 —我请你让我作为你的临时军官加入登船队\n我懂行, 知道怎么刺人和开枪。 所以我会像你一样冒生命危险... 咳... 哈! 拿下快速帆船后你再付我分成。 ";
			link.l1 = "你要求分得多少战利品? ";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "船长, 我不是贪婪的人。 我的分成是我的旧长艇能装的量, 大约200包白银。 据我所知, 快速帆船上至少有2000包白银, 所以我拿十分之一。 很公平, 你不觉得吗? ";
			link.l1 = "仅靠情报就拿十分之一战利品? 我在当地酒馆花一杯朗姆酒就能从醉汉那里买到这种情报。 不, 朋友, 我们道不同不相为谋! ";
			link.l1.go = "FalseTrace_4";
			link.l2 = "嗯。 我想我同意。 我接受你的提议, 亚当。 欢迎登船。 现在说说你的情报: 从哪里来, 到哪里去, 时间, 船名? ";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "你真是个吝啬鬼, 船长! 这样你会一无所获的! 再见! ";
			link.l1 = "祝你好运! 找另一个傻瓜来做你这见不得光的勾当吧! ";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "快速帆船的名字是'"+pchar.questTemp.FalseTrace.ShipName+"', 从卡塔赫纳出发, 驶往'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"'。 不过我们时间不多了。 最多两到三周。 如果三周内找不到她, 就结束了。 ";
			link.l1 = "那我们别浪费时间了! 冒险在召唤! ";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//设置遭遇战生成计时器
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//计时器
		break;
		
		case "FalseTrace_officer":
			dialog.text = "船长, 你有事吗? ";
			link.l1 = "没什么, 算了。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "船长, 你想见我吗? ";
			link.l1 = "我想你料到会有这一天... 白银在哪里, 该死的? 在哪里? 我在问你! 快速帆船的船长告诉我这是艘补给船! 你骗了我! ";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "冷静点, 船长。 我会试着解释一切。 ";
			link.l1 = "当然, 你会的! 我已经冷静下来了! 你现在没被吊在帆桁上只是因为我还不明白你的动机。 你明知没有白银还和我一起追这艘快速帆船。 所以请解释一下。 ";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "是的, 我确实骗了你, 船长。 但这是说服你做我需要的事的唯一方法, 去夺取... 咳咳! 夺取这艘该死的快速帆船\n但我保证会补偿你的损失。 现在让我告诉你为什么这么做。 你在快速帆船上找到一个女人了吗? 我看到船员把她带上了你的船... ";
			link.l1 = "嗯... 所以, 你需要那个女孩? 这就是你逼我开战并杀了很多人的原因? ! ";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "那是我妻子。 凯瑟琳.雷纳。 三个月前她和这个可怜的船长一起从我身边跑了。 我竭尽全力找到他们, 我做到了。 他们俩正要去'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"'。 我想不出更好的办法把凯瑟琳带回来, 并收拾那个偷妻子的家伙\n如果我告诉你真相, 你会走开。 所以我不得不编了个装满白银的快速帆船的诱人故事。 ";
			link.l1 = "哼... 你妻子离开你了, 不是吗? 很有意思! ";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "这是我合法的妻子, 我爱她, 没有其他人有权和她在一起! 那个无赖在我... 不在的时候, 给她讲了关于浪漫之类的美丽谎言。 你不了解女人吗? 她相信了那些鬼话, 傻姑娘, 就和他跑了。 ";
			link.l1 = "好吧, 听着, 我真的不关心你的家庭生活, 所以你自己和你妻子解决吧。 但你说过要补偿我的损失, 对吧? 我没听错吧? ";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "是的, 你没听错, 船长。 礼尚往来。 我现在没有钱, 但如果你把凯瑟琳和我带到'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"', 我会告诉你一个完全可靠的情报, 你可以毫不费力地找到一些金子。 ";
			link.l1 = "非常有趣。 为什么你不现在就告诉我这个完全可靠的情报? ";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "因为我现在还没有这个情报。 让我详细解释一下。 有个叫'斜眼索利'的幸运儿 —你听说过他吗? —他打算掠夺布鲁维尔德附近的一些金矿\n由于某些事件, 他将不得不把所有金子藏在某个隐蔽的地方, 并派几个卫兵保护。 他自己会步行去伯利兹或布鲁维尔德找船\n我在索利的船员中有个特工, 他会在'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"'等我。 一旦我们在那里抛锚, 他就会告诉我索利把宝贝藏在哪里\n你去那里, 消灭卫兵, 把所有金子拿走。 我本来打算自己去做, 但考虑到目前的情况, 我把一切都留给你。 不收费。 ";
			link.l1 = "你的故事听起来很像你之前那个装满白银的快速帆船的寓言。 你已经骗了我一次。 你怎么保证这次没撒谎? ";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "我向你保证。 我没有其他保证了。 但这是真的, 我发誓 咳... 哈... 该死的矿场! ";
			link.l1 = "好吧。 现在你可以走了, 我会考虑你说的话。 ";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "别考虑太久。 斜眼索利会回来拿他的宝藏, 你应该明白。 根据我的计算, 你只有两周时间到达'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"'。 ";
			link.l1 = "我会记住的。 现在去船员舱, 加入水手们。 我想在到达之前你最好和你妻子分开。 你现在可以走了。 ";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//计时器
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "船长, 你叫我? ";
			link.l1 = "是的。 亚当.雷纳, 我要逮捕你并关起来。 你骗了我, 我别无选择, 只能把你隔离并交给当局。 ";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "真的吗? 我料到你会这么做, 船长。 尤其是在你去货舱和那个偷别人妻子的混蛋谈过之后。 你决定站在他那边了, 不是吗, 船长? ";
			link.l1 = "与你无关。 你利用了我, 欺骗了我, 现在又想用荒谬的宝藏故事再次欺骗我! 水手长, 把他带走! ";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "哈, 没那么快, 船长... 你的水手长和其他人暂时进不来。 你没注意到我锁门了吗? 现在只有我们俩 —就你和我。 所以让我看看, 船长, 你有什么本事! ";
			link.l1 = "真的吗? 你真以为你有机会? ! 你会后悔的, 混蛋! ";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour 从40 hp 战士变成弱鸡
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "这样才对... 放下武器, 恶棍! 水手长! 给这个流氓戴上镣铐, 扔进货舱! ";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //释放囚犯
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //永久角色
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//不提供弹药 - 只是为了装备
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //取消计时器
			dialog.text = "谢谢你, 船长, 帮我把妻子带回来! 亚当.雷纳欠你一份人情, 他不会忘记的, 哈哈, 我发誓... 哈! 该死的矿场! 现在说说斜眼索利。 我的人已经把所有细节都告诉我了。 索利把所有宝贝都留在了圣胡安德尔诺特湾的一个洞穴里。 他本人现在在布鲁维尔德\n根据我的伙伴说, 你应该快点, 只有五天时间了。 带上你的人, 索利的匪徒很厉害, 他们会给你制造麻烦的\n是时候说再见了。 再次感谢你, 船长, 祝你好运! ";
			link.l1 = "祝你好运, 亚当。 别再惹你妻子了! ";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//计时器
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //取消计时器
			dialog.text = "哈! 船长, 我们到底为什么在这个海湾上岸? 我告诉过你我的人在'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"港等我! 你打算步行穿过丛林去那里吗? ";
			link.l1 = "猜错了, 亚当。 你真以为我会再次相信你的鬼话吗? 你觉得我是个十足的傻瓜吗? 这次我和你妻子做了交易。 ";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "什么? ! 哈! 和我妻子做了什么交易? 你在说什么, 你这个烂鱼? ! ";
			link.l1 = "因为你提供的虚假情报, 我夺取了一艘空的快速帆船, 杀了她的船长。 尽管现在后悔也晚了, 但我确实后悔了。 正如我所理解的, 你妻子爱上了那个水手。 这就是为什么她让我杀了你。 这就是为什么我们现在在这个海湾。 ";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "我不敢相信! 凯瑟琳... 真是个婊子! 好吧, 你也会得到应有的报应... 那么, 她答应怎么付你钱, 傻瓜? 她一分钱都没有, 甚至把所有珠宝都卖了才和那个船长跑了! ";
			link.l1 = "这不关你的事, 恶棍。 但现在是结束我们谈话的时候了。 我会送你下地狱, 你早就该去那里了! ";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "让我看看你有什么本事, 烂鲱鱼! ";
			link.l1 = "... ";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "啊! 你到底为什么攻击我的船, 混蛋? 我不明白... ";
			link.l1 = "别装羊了, 船长。 我知道你运的是什么货物。 我需要它。 ";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "货物? 哈哈! 你指望在这里看到什么货物? 我的货舱是空的! ";
			link.l1 = "你说什么, 恶棍! 再说一遍! ";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "我重复一遍 —我船上没有任何货物。 这艘快速帆船是一艘补给船, 正前往'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"'为部队运送炮弹和补给。 ";
			link.l1 = "你在蒙我。 你的货舱一定装满了白银。 我们谈完后我会去检查... ";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "我不知道谁告诉你有白银的。 但这完全是胡说八道... 我输给你了, 所以我投降。 这是我的剑。 现在你可以去检查货舱了。 它们是空的。 ";
			link.l1 = "投降? 不! 我不需要任何证人。 拿起你的剑战斗, 否则我就把你像羊一样开膛破肚。 ";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "你表现出理智是明智的。 我想我可以拿你换赎金... 嘿, 伙计们 —把船长扔进货舱! ";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//任务属性
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//任务属性
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "你杀了他, 你这个恶棍! 混蛋! 可怜的"+pchar.questTemp.FalseTrace.CapName+"! ";
			link.l1 = "这是怎么了? 你从哪里来, 亲爱的? ";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "你会为你所做的一切在地狱里燃烧。 去你的! ";
			link.l1 = "冷静点, 小姐! 别自找麻烦咒骂我 —否则我会让你跟着你的船长一起去! ";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "你... 你不敢对女人动手! ";
			link.l1 = "我甚至不需要动手。 我可以开枪打死你。 或者我直接把你扔到海里, 剩下的交给鲨鱼... 现在, 你还在等什么? 去我的船上。 别害怕 —如果你安静的话, 我不会让任何人伤害你, 我自己也不会碰你... ";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "你... 你打算怎么处理他? ";
			link.l1 = "这是怎么了? 你从哪里来, 亲爱的? ";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "可怜的"+pchar.questTemp.FalseTrace.CapName+"! 告诉我 —你要杀了他吗? 不要... ";
			link.l1 = "听着, 女士 —如果我想杀他, 我早就这么做了。 他会待在货舱里, 然后我会放了他或者可能拿他换赎金... 后者更有可能。 现在请做个好姑娘, 登上我的船。 别害怕 —如果你安静的话, 我不会让任何人伤害你, 我自己也不会碰你... ";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "你想从我这里得到什么? 像你说的那样把我扔给鲨鱼? 你毁了我的生活, 而我... ";
				link.l1 = "来吧, 亲爱的。 没人会把你扔到任何地方。 我只是想澄清情况, 因为我攻击这艘快速帆船是因为你, 而不是其他原因。 ";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "你想从我这里得到什么? "+pchar.questTemp.FalseTrace.CapName+"在哪里? 赎金? 你需要赎金吗? ";
				link.l1 = "好了, 女士, 让我们停止这些无意义的问题。 我叫你来不是为了这个。 有一个事实已经澄清了, 你会有兴趣听听。 ";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "因为我? 你是说你攻击我们的船并杀了我心爱的人是我的错? 可怜的"+pchar.questTemp.FalseTrace.CapName+", 他对你做了什么? 你会为你所做的一切向上帝忏悔... ";
			link.l1 = "又是老一套! 我们回到鲨鱼的话题好吗? ";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://节点交叉点 - 开始
			dialog.text = "";
			link.l1 = "现在安静了? 太好了。 现在听我说! 我攻击这艘船, 是因为我得到情报说她载有大量白银。 而这个情报来自我亚当.雷纳。 ";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "啊! 什么? ! 亚当? 他在哪里? 他在这里吗? ";
			link.l1 = "我看你知道这个名字... 凯瑟琳。 而且, 如你所见, 我已经知道关于你的一切。 我猜亚当.雷纳是你的丈夫, 对吗? ";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "是的。 我是这个怪物的妻子。 我曾误以为这场噩梦终于结束了... 他雇你来抓我吗? ";
			link.l1 = "总的来说结果就是这样。 亚当骗我说有白银, 这样我就会夺取'"+pchar.questTemp.FalseTrace.ShipName+"'号快速帆船。 显然, 他决心要把你带回来。 一刻钟前他向我解释了他的所有行为。 ";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "那... 他想要什么? 他告诉你什么了? ";
			link.l1 = "他想要他合法的妻子回到他身边。 作为欺骗我的补偿, 他会向我提供斜眼索利的黄金情报。 而我打算把你们俩都带到'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"'。 ";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "不... (哭泣) 我不想回到这个无赖身边! 我费了很大劲才逃离他并掩盖行踪, 但他还是找到了我... 恶棍! 土匪! 该死的小偷! ";
			link.l1 = "冷静点, 凯瑟琳... 注意你的言辞。 毕竟他是你丈夫。 而且他说他爱你。 ";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = " (哭泣着) 我丈夫? 你知道我丈夫是谁吗? 他是'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"'最残忍的土匪, 一个前囚犯, 一个罪犯! 他是个卑鄙肮脏的野兽, 对他来说我只是一个泄欲的工具! ";
			link.l1 = "你结婚前没看清这些吗? ";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "起初, 他不一样... 他的过去在我看来很浪漫... 但最终一切都变了。 我甚至不想见到他, 更不用说和他一起生活了, 你能理解吗? 我不想! 尤其是在这次快速帆船袭击之后, 这是他策划的! ";
			link.l1 = "嗯... 那么, 我该怎么处理你呢, 亲爱的女士? ";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://节点交叉点 - 结束
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "怎么处理? 我知道该怎么做。 你是罪恶的工具, 多亏了我丈夫的行为。 你杀了一个无辜的人, 唯一一个对我好的人。 弥补你的罪过, 船长。 杀了亚当。 就在我眼前。 我想看到这个混蛋死去, 我想往他的尸体上吐口水\n等他死了, 我会告诉你他把宝藏藏在哪里。 那个醉鬼有一次告诉我他的藏匿处, 哈哈, 他甚至不记得了! ";
				link.l1 = "呵! 我看你也是个残忍的女人, 凯瑟琳! ";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... 快速帆船的船长。 你把他关起来了。 和他谈谈, 我求你了! 他会为我们的生命和自由给你一些东西! 他会想出办法的! 我... 我不想回到亚当身边, 从现在起"+pchar.questTemp.FalseTrace.CapName+"就是我丈夫! 我求你 —别把我带回亚当身边, 带回那个怪物身边! ";
				link.l1 = "嗯。 有趣。 我的囚犯能给我什么? 我可以从当局那里拿到他的赎金, 我也可以拿到斜眼索利的黄金... ";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "看看谁在谈论残忍。 你还好意思说。 航行到'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"', 照亚当告诉你的做, 只是不要在港口靠岸, 而是在最近的海湾。 我们三个人去那里, 你杀了那个混蛋\n一旦完成, 我会告诉你藏匿处。 我发誓, 我不骗你。 我相信你更相信我的话而不是亚当的, 他骗过你一次, 对吧? 你说呢, 船长? ";
			link.l1 = "是啊... 人们说夫妻果然是天生一对。 我看着你, 凯瑟琳, 觉得你和亚当是绝配... 如果你这么想让他死, 你大可以在他喝醉睡着时捅死他... 水手长! 把她带走! ";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "我讨厌那些试图欺骗我并利用我达到自己目的的无赖。 好吧, 凯瑟琳, 我同意你的提议, 因为我清楚亚当不可信。 但如果你也骗我, 我发誓即使在欧洲也会找到你, 给你脑袋来一枪。 现在滚吧。 水手长! 把她带走! ";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "你会后悔的... 我发誓, 我... ";
			link.l1 = "水手长! 看好她, 在我们到达'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"'之前一直盯着她! ";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "什么事实? 你打算怎么处理我们? 你为什么夺取我们的船? ";
			link.l1 = "你能让我说句话吗, 还是我该命令水手长用堵嘴布让你安静? ! ";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "索利的黄金? 你真的相信这个无赖? 他会再次骗你, 这就是他的方式! 和你的囚犯谈谈! \n"+pchar.questTemp.FalseTrace.CapName+"是个真正的绅士, 他不会食言, 也不会对你撒谎! ";
			link.l1 = "你没说服我, 女士。 我和你的船长没什么好谈的。 我会拿他换赎金, 从亚当那里拿到索利的黄金。 如果亚当再骗我, 我就算追到天涯海角也会找到他, 让他后悔出生... 水手长! 把她带走! ";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "说实话, 我不信任亚当... 我讨厌被人操纵。 好吧, 我会和你的船长谈谈, 看看他能告诉我什么。 你现在可以走了... 水手长! 把她带走! ";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "你是个残忍无情的人! 我发誓我... ";
			link.l1 = "水手长! 看好她, 在我们到达'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"'之前一直盯着她! ";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "现在一切都结束了... 可怜的"+pchar.questTemp.FalseTrace.CapName+"得到了复仇, 我现在可以自由呼吸, 称自己为寡妇了... ";
			link.l1 = "我已经履行了我的部分协议, 凯瑟琳。 现在轮到你了。 ";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "当然, 船长。 我的丈夫 —感谢上帝, 现在是前夫 —是个土匪, 你已经知道了。 由于担心可能的搜查, 他不在家里存放掠夺来的赃物。 他组织了一个藏匿处 —但他有一次说漏了嘴。 不过, 他藏得很巧妙 —从岸上无法进入那个地方。 ";
			link.l1 = "非常有趣... 它在哪里? ";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "在伊斯帕尼奥拉岛附近的一个小岛上。 在灯塔里。 ";
			link.l1 = "太子港灯塔! 它位于岛上! ";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "大概是这样。 你可以在那里找到战利品。 你会看到的。 就这样。 再见, 船长。 ";
			link.l1 = "等等... 凯瑟琳, 如果你能的话, 请原谅我。 我希望那个为你所有不幸负责的人的死至少能让你得到一些解脱。 我真的很抱歉... ";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "我不需要你的后悔, 船长。 你做了我要求你做的事 —我告诉了你想知道的一切。 现在再见, 让我独自悲伤... ";
			link.l1 = "再见, 凯瑟琳。 ";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//允许生成军官
			//LAi_LocationDisableOfficersGen("Mayak7", true);//禁止生成军官
			locations[FindLocation("Mayak7")].DisableEncounters = true;//关闭遭遇战
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "肮脏的恶棍! 他竟然杀了全部四个人! 难以置信! ";
			link.l1 = "没想到会这样吧, 凯瑟琳? 我很难被杀死。 你两面三刀玩得很好, 我得说! ";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "你杀了我的人。 你真以为我会让你活着? 你以为亚当的死让我满意了? 不! 你不会离开这个地方。 离这个岛不远有艘船, 她会把你的破船和你一起击沉! \n现在, 你想对我做什么就做吧。 ";
			link.l1 = "亲爱的, 我没告诉过你吗? 如果你骗我, 你会掉脑袋的? 狡猾的魔鬼! 你死了会更安全。 这颗漂亮的脑袋现在就要吃枪子了... ";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "我同情你, 凯瑟琳。 你对复仇的渴望最终没给你带来任何好处。 我打算把你留在这个岛上, 听天由命 —你会在这里等当地渔民发现你, 把你带到伊斯帕尼奥拉岛。 愿上帝评判我们所有的行为... ";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "你才应该祈祷, 怪物! 凶手! 救命! 去你... ";
			link.l1 = "我听够了。 ";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			// belamour legendary edition 如果没装备手枪或步枪, 就给一把 -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// < —legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "愿你淹死! 愿你的船触礁! 愿你... ";
			link.l1 = "再见, 凯瑟琳。 ";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//允许生成军官
			locations[FindLocation("Mayak7")].DisableEncounters = false;//打开遭遇战
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "啊-啊, 这就是杀亚当的凶手! 凯瑟琳说得对, 这个混蛋来抢藏匿处了! ";
			link.l1 = "什么? 凯瑟琳? 你们是谁? ";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "我们是谁? 我们是亚当.雷纳的朋友, 他被你谋杀了。 他是我们兄弟会的头目。 现在我是头目, 我叫"+GetFullName(npchar)+", 我会为你杀了我老大和虐待他妻子的行为惩罚你。 ";
			link.l1 = "虐待? 你到底在说什么? ";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "你从背后捅了亚当, 你这个肮脏的叛徒, 你强迫他妻子告诉你亚当把金子藏在哪里, 然后把可怜的女人留在荒岛上等死\n但她活了下来, 她请我们帮助她, 主持正义。 我们等了你好几天。 现在你来了, 混蛋! ";
			link.l1 = "哈哈! 绝对是凯瑟琳的风格... 现在听着, 我确实杀了亚当, 但那是因为他妻子真的让我杀他。 那是为了给她爱人的死报仇。 她告诉我在哪里可以找到藏匿处来报答我... ";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "别诋毁可怜的寡妇, 人渣! 那她为什么来找我们? 她提出让我们拿走所有金子来换你的命。 她不想要钱, 她想要你的命! 为丈夫之死的神圣复仇! \n但我发誓, 她不会在贫困中死去, 就像我的名字是"+GetFullName(npchar)+"一样真实, 现在是你死的时候了, 懦夫! ";
			link.l1 = "一派胡言, 多么精彩的演讲。 哦, 她来了, 渴望亲自观看这场喜剧... 先生们? ";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "你真是个糊涂虫, 船长! 让装满白银的快速帆船跑了... 我错看你了。 再见! ";
			link.l1 = "再见, 亚当。 ";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "我警告过你, 船长, 我们只有两周时间! 现在斜眼索利肯定已经把所有战利品都拿走了。 你这么糊涂不是我的错。 再见! ";
			link.l1 = "是的, 我的错。 再见, 希望我们不再见面, 你给我带来的只有厄运。 ";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "呵! 终于来了! 我们等累了, 这些该死的蚊子... 等等... 索利呢? 我不明白... ";
			link.l1 = "索利不会来这里。 我代表他行事... 所以要么你把金子给我, 要么你就死定了。 ";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "啊! 我们走着瞧! 伙计们, 到我这里来! 拿起武器! ";
			link.l1 = "死得真愚蠢, 来吧, 拾荒者们! ";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "你履行了你的协议, 船长。 谢谢你信任我。 别担心亚当, 我会把他送到合适的地方。 他会得到应有的惩罚。 ";
			link.l1 = "我不在乎亚当。 你答应的那艘船呢? ";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "是的, 是的, 当然。 从今天起算... 是的... 12-14天后, 从'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+"'将有一艘装载黄金矿石的重型大帆船起航前往欧洲。 她将由一艘护卫舰或轻巡洋舰护航\n所以准备好, 这是一笔丰厚的战利品, 但也有风险。 不过, 我相信你会成功, 你轻松地击败了我的抵抗... 你必须在两周内到达'"+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+"'并准备伏击\n记住, 你的目标是一艘有单艘护航船的重型大帆船。 我想就是这样。 剩下的就看你了。 ";
			link.l1 = "我明白了... 好吧, "+pchar.questTemp.FalseTrace.CapName+", 再见。 也许我该祝你和凯瑟琳好运? 希望你们俩能好好的。 很遗憾我们在这种悲伤的情况下相遇。 ";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "谢谢你, 船长。 正如我之前所说, 你有一些高贵品质。 我希望你能得出正确的结论: 诚实的行为比不光彩的行为给你带来更多的利益。 致力于为你的国家服务, 你会成为一名伟大的海军水手。 ";
			link.l1 = "我会考虑你的话。 好吧, 现在再见! ";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //打开遭遇战
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}