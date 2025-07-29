void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "你想要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "你很厉害"+GetSexPhrase("","啊")+"... 该死的厉害"+GetSexPhrase("","啊")+"。 但在你完成任务前, 听我说完。 我肯定我要说的话会让你感兴趣。 ";
			link.l1 = "我想你可以在死前说些遗言。 但别抱希望, 你出不了这个山洞。 ";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "港口主管, 嗯? 他派你来取我的人头? ";
			link.l1 = "你还是这么敏锐。 ";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "他派你来杀我, 不是吗? 不是找我, 不是抓我 —是杀我。 ";
			link.l1 = "没错。 那又怎样? ";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "哈... 你真是个"+GetSexPhrase("蠢货","小傻瓜")+"。 你有没有想过为什么他这么在乎我死, 而不是让我烂在牢房里? 没想过? 你根本不知道你要救的是谁。 那个港口的蜘蛛在这地方织满了谎言, 而你, "+GetSexPhrase("小子","亲爱的")+", 深陷其中。 \n你以为他是个诚实的官员? 哈! 他只有在睡觉的时候才会梦到诚实。 他把情报卖给海盗和荷兰人, 背叛信任他的人。 这种害虫就该埋进土里! ";
			link.l1 = "谁的靴子不踩点泥呢。 你看起来也不像个修士。 ";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "我不是修士, 也不假装是。 我的刀刃从不说谎。 一眼看去, 别人就知道死亡降临了。 我不会对猎物微笑, 也不会在知道它已注定死亡时和它握手。 不, 我的意图很明确。 那个官僚呢? \n他背叛所有信任他的人, 同时假装在帮助他们。 他比我埋进坟墓的任何混蛋都更坏。 ";
			link.l1 = "假设你说的是真的。 谁雇的你? ";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "我不会给你名字 —我甚至不知道。 但他是被那混蛋伤害过的人, 一个寻求正义... 或者复仇的人。 随便你怎么叫。 五百达布隆买那个腐败官员的人头! 帮我, 我们分钱。 ";
			link.l1 = "别说了! 你为了保命什么都敢说。 我让你说了, 现在该去死了。 ";
			link.l1.go = "Naemnik_7";
			link.l2 = "故事不错。 但我不会就这么信你。 除了你的话还有别的吗? 证据, 证人? 还是这只是另一个求生的伎俩? ";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "这些羊皮纸是在一个私掠船船员的住处发现的, 那是我雇主在战斗中击败的海狗。 那个恶棍的情报正是来自港口主管本人。 里面详细记录了船只航线。 出发时间和货物性质。 这些船后来都被掠夺了, 船员被屠杀或消失在无尽的蓝色中\n注意看 —这些笔记的笔迹和官方舱单上的完全一致。 这些证据会揭穿叛徒的真面目。 我的雇主希望这些文件在他尸体上被发现, 法官的长凳不够用\n这个恶棍权势太大, 口袋里有无数腐败的盟友。 如果他被带上法庭, 会从正义的掌握中溜走。 这种害虫不配活在上帝的造物中, 只有遗臭万年的死亡才配得上这种背叛。 ";
			link.l1 = "奸诈的狗! 人们把财富托付给他, 他却把他们的性命卖给杀手和强盗! 算我一个盟友, 这种生物不配活在上帝的天下。 ";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "我弄到了他住所的钥匙 —通过修理他豪宅家具的木匠。 一切按计划进行, 直到我发现他和别人同住。 当我进去执行正义时, 他的妻子在场\n她的意外出现让我犹豫了。 没有悬赏她的命, 而且王室的人会更卖力地追捕杀了贵妇的人。 于是我改变计划, 在海关附近等他。 ";
			link.l1 = "该死的! 现在全城戒备 —我们不能像以前那样公开行动了。 我们还有什么办法? ";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "我一直在监视小镇, 等待骚动平息。 我尝试后, 那个懦夫赶紧把妻子藏了起来。 我亲眼看见她登船离开港口\n现在他独自一人 —完成我们开始的事的最佳时机。 在黑暗的掩护下, 你可以潜入他的巢穴, 结束这件事。 然后把这些该死的文件放在显眼的地方, 让所有人都知道他心中的腐败\n但对我来说, 城门紧闭。 然而你... 你可以在我失败的地方成功。 没有卫兵搜捕你的脸, 你会轻松通过他们的监视。 他的房子在城市监狱附近。 五百达布隆! 叛徒死后, 一半赏金归你。 ";
			link.l1 = "就这样吧。 我将亲手把这个恶棍送去见他的造物主。 这些文件会留在他的住所 —让所有人都知道他的背信弃义。 等我回来, 正义伸张后我会回来。 ";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "你为什么像脚陷在石灰里一样站在那里不动? ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "你? 搞什么鬼? 你怎么进来的? ";
			link.l1 = "我怎么进来的根本不重要。 而且我认为在内心深处, 你明白我为什么来。 ";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "不, 我不明白! 如果你是为了赏金, 明天来行政办公室, 我会给你一切。 ";
			link.l1 = "别装无辜了! 我什么都知道。 你把客户船只的情报卖给海盗。 这种卑鄙的人不配担任这样的职位, 更不配和诚实的人生活在一起。 先生, 你的位置属于你自己的同类 —地狱。 ";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "哦, 不-不-不! 不! 你完全搞错了! 他-他们逼我的... 他们来找我, 威胁说如果我不帮他们就对付我的家人... 你不明白... ";
			link.l1 = "我受够了你可悲的借口! 我手里有你的笔记, 你在上面要求从情报中分成! 你的虚伪令人作呕, 我不再打算容忍了。 拔出你的武器自卫吧, 如果你有勇气的话! ";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "那么, 有什么消息? 我们的事完成了吗? ";
			link.l1 = "你怀疑我吗? 那可怜虫拼命想找些可怜的借口, 但没用。 我按我们约定的, 把该死的文件放在显眼的地方了。 ";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "像他这样的懦夫永远相信可以用卑鄙的谎言和金钱从正义的刀刃下购买宽恕。 ";
			link.l1 = "好吧, 他再也不用想了。 把我的报酬给我, 我要走了。 ";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "这是你的达布隆, 应得的。 干得好, 我承认。 但记住 —如果我们第一次交锋时我手握更锋利的剑, 我们的命运可能会大不相同... 让你后悔终生。 在那些狭窄的房间里, 合适的武器无法真正挥舞, 所以我只带了这把可怜的牙签, 想着迅速解决你\n如果我预见到事情会如何发展, 我会用更适合我气概的刀刃武装自己。 ";
			link.l1 = "哈! 我们的亡友声称你像罗兰在龙塞斯瓦列斯峡谷前一样武装! 你证明了自己是个什么样的圣骑士。 ";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "呵呵。 恐惧投下的阴影很大, 不是吗? 你亲眼见过我差点刺穿你心脏的那把微不足道的铁家伙。 ";
			link.l1 = "你是说如果手里有更重的钢刃, 你可能会成为我的劲敌? ";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "在中等重量刀刃的掌握上, 无人能超越我的技能 —我以生命之血起誓。 你怀疑吗? 那好。 我会传授你一些让我在无数危险中幸存的狡猾招式。 仔细听 —这些不是吹牛, 而是有一天可能让你免于早逝的智慧。 这种神秘知识很少分享给除了最有价值的学生之外的人。 ";
			link.l1 = "... ";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("一个小时过去了... ", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "... ";
			link.l1 = "我看你确实是这门手艺的大师。 谢谢你的教导。 但如果我们的事完成了, 我必须走了。 ";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "再见, "+GetSexPhrase("船长","美丽的女士")+"。 希望我们不再交锋。 送你去见造物主会让我难过。 哈哈。 ";
			link.l1 = "即使我烂醉如泥。 单腿站立, 你也没有一丝机会! 再见, 雇佣兵。 ";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);
			
			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);
			
			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");
			
			AddSimpleRumourCity("听说港口主管被发现死在自己家里。 在他身上发现了文件, 证明他参与了船只失踪事件。 想想看 —这对我们镇是多大的耻辱... ", "Beliz", 30, 1, "");
			AddSimpleRumourCity("你听到消息了吗? 有人潜入港口主管的房子, 杀了卫兵, 把他解决了。 在尸体上发现了笔记, 上面有失踪船只的航线 —是他自己的笔迹! 王室的仆人, 却是真正的叛徒! 罪有应得! 这些年总督在哪里? ", "Beliz", 30, 1, "");
			AddSimpleRumourCity("港口主管死了! 就在自己家里被杀! 卫兵被屠杀, 在他的财物中发现了地图, 标注着失踪船只的航线。 毫无疑问 —他是失踪事件的幕后黑手! 正义终于降临到这个恶棍身上。 ", "Beliz", 30, 1, "");
			break;
	}
}