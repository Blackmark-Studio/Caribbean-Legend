void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "... 及圣灵。 阿门。 ";
			link.l1 = "我很少在教堂看到军人。 ";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "许多人认为信仰与刀剑互不相容。 但医生切割不是为了治愈吗? 父亲惩罚不是为了保护吗? ";
			link.l1 = "听起来像是辩解。 ";
			link.l1.go = "Alamida_church_3";
			link.l2 = "这其中有智慧。 有时残酷是必要的。 ";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "你错了。 这不是辩解 —这是理解。 当我刚开始服役时, 每一次死亡都... 很艰难。 但后来... 我开阔了眼界。 ‘残酷是至高之爱的体现。 ’";
			link.l1 = "我不打扰您祈祷了。 ";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "是的... 是的! 这正是引导我走上这条路的人所说的。 ‘没有力量的仁慈是无用的, 就像没有手的剑。 ’";
			link.l1 = "我不打扰您祈祷了。 ";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "为我们所有人祈祷吧。 为我们所做的... 和我们必须做的。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "短缺百分之七。 上次是百分之五。 像废弃花园里的杂草一样增长... ";
			link.l1 = "镇上有新总督吗? ";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "什么? 啊, 不。 大人在那边的角落里。 我是费尔南多.德.阿拉米达, 皇家监察官。 ";
			link.l1 = "这工作一定很困难。 ";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "你知道打击腐败最困难的部分是什么吗? 有罪的人不一定是坏人。 他们有孩子, 有家庭。 每次你都必须提醒自己: 毒药仍然是毒药, 即使盛在金杯里。 ";
			link.l1 = "但能如此严厉地评判吗? 我们都是凡人... ";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "你太心软了。 只有监狱才能改造他们。 ";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "对狼的仁慈就是对羊的残酷。 一位智者曾这样说。 随着每一天的过去, 我越来越理解他的智慧。 ";
			link.l1 = "我不再打扰您工作了。 ";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "嗯。 你知道, 我曾经也这么想。 但监狱太简单了。 需要更多的东西... 净化。 ";
			link.l1 = "我不再打扰您工作了。 ";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "是的。 文件不会等待。 尽管有时我觉得这里的每个数字背后都隐藏着某人的命运。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "我在认真听, " + GetAddress_Form(NPChar) + "? 是什么让您在街上就这样接近我? ";
			link.l1 = "您在人群中很显眼。 ";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "费尔南多.德.阿拉米达, 皇家监察官。 你是今天第一个如此好奇的人。 每个人都躲藏, 每个人都害怕我。 然而诚实的人没什么可害怕的。 这告诉我们什么? ";
			link.l1 = "您的名声让他们害怕? ";
			link.l1.go = "Alamida_city_3";
			link.l2 = "诚实的人很少? ";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "有趣。 我也曾这么想。 直到我明白 —恐惧能净化。 当一个人害怕时, 他们会变得更诚实。 更接近他们的本性。 更接近上帝。 ";
			link.l1 = "有意思的想法。 我得走了。 日安, 费尔南多先生。 ";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "有趣... 你和我认识的一个人想法一样。 可惜不是每个人都能接受这个真理。 ";
			link.l1 = "有意思的想法。 我得走了。 日安, 费尔南多先生。 ";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "好? 是的, 也许。 只要它是正义的。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "还有什么事吗, 船长? ";
			link.l1 = "没有了, 费尔南多先生, 只是打个招呼, 没别的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "一位持剑的少女? 嗯, 我从没想过有生之年能看到这样的景象。 你是谁, 小姐, 竟敢攻击‘神圣慈悲号’? ";
				link.l1 = "海伦.麦克阿瑟船长。 你脸上的惊讶表情我很熟悉。 ";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "你怎么敢? ! 攻击‘神圣慈悲号’? ! 一艘承载着国王意志和... 好吧。 既然你在这里, 告诉我 —为什么? 为什么选择这种疯狂行为? ";
				link.l1 = "我是海盗。 而你的大帆船肯定装满了宝藏。 ";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "多么美丽的船... 我必须拥有它。 ";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "我是你国家的敌人, 费尔南多先生。 ";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "只是因为。 为什么不呢? ";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "你多么像圣母玛利亚, 我们船的守护者... 同样美丽。 但她保护正义之人, 而你... ";
			link.l1 = "我是来拿你的船的。 在这里说恭维话没用, 费尔南多先生。 ";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "真遗憾。 那我得教你谦卑了。 既然没有其他办法, 就用武力吧。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "啊, 是的。 当然。 黄金。 总是黄金。 腐蚀灵魂的毒药。 为了它你将死去。 ";
			link.l1 = "别这么戏剧化。 这只是生意。 ";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "船舱里的每一枚硬币都是罪人支付的净化费用。 你想要? 那就分享他们的命运。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "许多人觊觎‘神圣慈悲号’。 它的美丽是许多船长的末日。 ";
			link.l1 = "那我将是第一个拥有它的人。 ";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "没有力量的仁慈是无用的, 就像没有手的剑。 你今天将学到这一课。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "原来如此。 又一个嫉妒帝国伟大的人。 ";
			link.l1 = "什么伟大? 你们僵化的方式阻碍了这个世界的发展。 ";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "别自欺欺人了。 对西班牙的恐惧让你更诚实。 更接近你的本性。 你现在就会明白。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "疯子。 或者也许你是作为考验被派给我的? ";
			link.l1 = "不是所有事情都需要理由, 先生。 ";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "他说像你这样的人最危险。 但这只会增强我在战斗中的力量。 ";
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "如此坚强的意志... 如此的决心... ";
				link.l1 = "惊讶吗? ";
			}
			else
			{
				dialog.text = "不错。 我已经很久没有遇到过值得一战的对手了。 ";
				link.l1 = "我不会给你休息的时间。 ";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "有人警告过我... 关于这样的考验。 关于能动摇战士信仰的美丽。 ";
				link.l1 = "费尔南多先生, 您总是把简单的事情复杂化吗? ";
			}
			else
			{
				dialog.text = "主给予为正义事业服务的人力量。 不过... 有时我不再确定我在为什么服务。 ";
				link.l1 = "有疑虑吗? ";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "简单? 不... 一定有更高的意义。 这是一个考验。 我不能错。 ";
			}
			else
			{
				dialog.text = "不。 他教导我不要怀疑。 永远不要。 ";
			}
			link.l1 = "... ";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "等等... 等等。 你赢了。 我受伤了, 正在流血。 让我在死前祈祷吧。 ";
			link.l1 = "非常好。 ";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "主啊... 宽恕我的罪孽, 在这考验的时刻赐予我力量。 保佑我倒下的同志们的灵魂。 忠诚的水手们, 他们怀着相信自己承载着正义的信念而死\n父亲, 我努力按照你的教导生活, 为打击不公而奋斗。 但你的儿子玷污了阿拉米达家族的荣誉。 宽恕我\n祖国... 我发誓忠诚而真实地为您服务。 但我的热情, 我的愤怒... 我变成了我试图对抗的人\n迭戈... 也许他撒谎了? 一直以来... 如果是这样, 我真不幸\n主啊, 也保佑这个女人。 也许在您最后的慈悲中, 您把她派给我... 让我看到自己偏离了多远。 阿门。 ";
			}
			else
			{
				dialog.text = "主啊... 宽恕我的罪孽, 在这考验的时刻赐予我力量。 保佑我倒下的同志们的灵魂。 忠诚的水手们, 他们怀着相信自己承载着正义的信念而死\n父亲, 我努力按照你的教导生活, 为打击不公而奋斗。 但你的儿子玷污了阿拉米达家族的荣誉。 宽恕我\n祖国... 我发誓忠诚而真实地为您服务。 但我的热情, 我的愤怒... 我变成了我试图对抗的人\n迭戈... 也许他撒谎了? 一直以来... 如果是这样, 我真不幸\n圣母玛利亚, 为我们祈求上帝, 赐予我们您的慈悲。 阿门。 ";
			}
			link.l1 = "我不认识你了, 费尔南多先生。 你现在看起来像另一个人。 你刚才在说谁? ";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//埃伦
		case "Alamida_Helena":
			dialog.text = "我的船长, 恭喜! 多么激烈的战斗。 那个船长很有技巧, 哦, 太有技巧了。 但你... 你证明了自己更优秀。 我为你感到多么骄傲... ";
			link.l1 = "谢谢你, 我的爱人。 你受伤了吗? ";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "不, 没有。 不过我觉得我们有几次处于边缘 —无论是在登船前还是登船时。 你呢, 你还好吗? ";
			link.l1 = "我很好, 再次感谢。 去船舱休息吧, 我很快就来。 ";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//玛丽
		case "Alamida_Mary":
			dialog.text = "查尔斯, 你还好吗? 我尽快赶来了, 还好。 ";
			link.l1 = "我很好, 谢谢你, 亲爱的。 不过这是一场艰苦的战斗。 ";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "我很高兴! 但是... 听着, 查尔斯? 我们为什么要攻击这些人? 主不会原谅我们的, 不会。 这艘船... 像一座伟大的圣殿。 当我看到它时, 我的心颤抖了, 就像我第一次看到真正的教堂, 而不仅仅是在书中。 现在它在流血! ";
			link.l1 = "玛丽... 你知道外表可能具有欺骗性。 在虔诚的面具后面, 是那些从普通信徒那里拿钱的人 —就像你一样。 明白吗? ";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "我... 我相信你, 查尔斯。 好吧。 只是... 让我们至少把在这里找到的一些黄金捐赠给真正需要的人吧? 这会让我心安。 ";
			link.l1 = "我们会的, 玛丽。 我保证。 现在整理一下思绪, 试着冷静下来。 一切都结束了。 ";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//汤米
		case "Alamida_Tommi":
			dialog.text = "哈, 好吧, 恭喜你获胜, 船长! 这才叫生意! 这艘大帆船上的战利品可真多! ..";
			link.l1 = "你今天的笑容比平时更灿烂, 汤米。 ";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "当然! 这么多战利品。 还有这么一场战斗。 让我想起了革命。 还有... 嘿。 ";
			link.l1 = "怎么了, 汤米? 来吧, 说出来。 ";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "他们把整艘船装饰得像一座漂浮的大教堂。 还从各地收集了这么多黄金。 真正的天主教狂热分子! 耻辱又可笑。 ";
			link.l1 = "这是一艘国库船, 汤米。 不是教堂船。 ";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "在我们看来没什么区别。 不管怎样, 我很高兴给那些老爷和天主教徒一个教训! 两者我都受不了。 我今天过得很愉快, 哈哈哈! ";
			link.l1 = "你从未改变! 好吧, 解散。 这里一切都在控制之中。 ";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//提钦吉图
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "查尔斯船长, 我们赢得了胜利。 这是一场艰苦的战斗。 即使是提钦吉图也觉得很难, 而我是村里最好的战士之一。 ";
				link.l1 = "没错, 我的朋友。 他们确实是值得尊敬的对手。 ";
			}
			if (startHeroType == 2)
			{
				dialog.text = "蒙托亚先生, 船是我们的了。 ";
				link.l1 = "很好, 提钦吉图。 我也刚在这里结束。 ";
			}
			if (startHeroType == 3)
			{
				dialog.text = "帕特森船长, 船上的最后抵抗被粉碎了。 ";
				link.l1 = "你迟到了, 提奇! 下次最好跟着我。 不过我不是说我不能独自处理... ";
			}
			if (startHeroType == 4)
			{
				dialog.text = "麦克阿瑟船长, 你没事吧? ";
				link.l1 = "是的, 提钦吉图, 我很好, 谢谢你的关心。 别再怀疑你的船长了 —我自己处理得很好。 ";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "战斗中灵魂告诉我这个。 并问我为什么杀他们。 现在我问你同样的问题。 提钦吉图在他们眼中看到, 他们还不是恶棍。 ";
				link.l1 = "啊, 我能告诉你什么呢? 我没有答案, 提钦吉图。 ";
			}
			if (startHeroType == 2)
			{
				dialog.text = "我想问你一个问题, 蒙托亚船长。 ";
				link.l1 = "我在听。 ";
			}
			if (startHeroType == 3)
			{
				dialog.text = "如果您允许, 威廉船长, 提钦吉图想问您一个问题。 ";
				link.l1 = "允许。 ";
			}
			if (startHeroType == 4)
			{
				dialog.text = "我不是怀疑, 我是担心你, 船长。 ";
				link.l1 = "好了, 好了。 我从你眼里看得出来你还想问我别的事。 ";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "嗯, 如你所说, 船长。 我们在这里结束了吗? ";
				link.l1 = "是的。 我再四处看看, 然后和其他人会合。 ";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "这些人, 他们和你不是同一个部落的吗? 他们不是西班牙人吗? 你为什么决定攻击? ";
				link.l1 = "没错。 但印第安部落之间不也互相争斗吗? 或者一个部落内部没有争吵和纷争吗? ";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "这艘船看起来像教堂。 你讨厌教堂和白人的神吗? ";
				link.l1 = "一点也不。 但这只是装饰, 你看? 这是一艘国库船。 不过你不会明白 —我听说你们的人甚至不知道什么是税收。 幸运的家伙。 ";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "是的。 是真的。 麦克阿瑟船长, 我们为什么要攻击这艘漂浮的教堂? ";
				link.l1 = "漂浮的教堂, 哈哈哈! 不, 不。 这是一艘国库船。 嗯, 我看你不太明白。 好吧, 他们当时载着黄金。 我能想象当我告诉扬我击败了费尔南多.德.阿拉米达时, 他会有多骄傲! ";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "嗯, 你说得对, 船长。 但印第安人之间发生的这种情况比白人少。 ";
				link.l1 = "也许吧。 好吧, 这个人... 在妨碍我。 ";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "没错, 马斯科吉人没有城堡和税收。 ";
				link.l1 = "正是。 你可以走了, 反正你已经迟到了。 稍后我们会决定如何处理这艘美丽的大帆船。 我不喜欢这些大船, 但该死的, 她真漂亮。 ";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "提钦吉图也为你感到骄傲, 船长。 并祝贺你在这场艰苦的战斗中获胜。 ";
				link.l1 = "谢谢你。 现在让我们开始分配战利品吧。 ";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "妨碍你, 蒙托亚先生? ";
			link.l1 = "正是。 这个群岛对我们俩来说太小了。 而且我在这里对我们的国家更有用。 记得可可叶 —他对他的兄弟们造成的伤害比好处多。 这里也是一样。 ";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "现在我明白了。 提钦吉图可以走了吗, 船长? ";
			link.l1 = "是的, 走吧。 我也很快就会加入你们。 ";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//关于暴露武器的评论
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("嘿, 挥舞武器是怎么回事? ! 马上把它收起来! ", "我命令你立即收起武器! ", "嘿, " + GetAddress_Form(NPChar) + ", 别吓唬人了! 把武器收起来。 ");
			link.l1 = LinkRandPhrase("好吧, 我把它收起来... ", "已经收好了。 ", "如你所说... ");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("去你的! ", "我想我会用它的! ", "时机合适时我会收起来的。 ");
			link.l2.go = "fight";
		break;
		
	}
}