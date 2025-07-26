// 杰西卡.罗斯 - 不死生物与最终BOSS
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 暗礁上的战斗
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "你! 是你带她来的! 她是他的血肉! 是她的血肉! whore 的女儿来到了母亲的坟墓前! 她会死的! 你阻止不了! 别挡在杰西卡的路上! 让复仇属于我! ";
			link.l1 = "... ";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "哈! 你伤不了我! \n元素听令 --风。 水。 土。 火助我! \n让死者崛起, 让火焰燃烧, 让流水守护桥梁, 让狂风将你卷起摔在地上! \n好好享受吧! ";
			link.l1 = "... ";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "哈! 你伤不了我! \n让更多死者崛起攻击, 让火焰灼烧岩石, 让狂风将你卷起摔下, 让大地吸收你的力量! \n尽情享受吧! ";
			link.l1 = "... ";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "哈! 你伤不了我! \n让毒药覆盖我火焰之刃, 让狂风拥抱你, 让流水夺走你的敏捷! \n去死吧! 哈哈哈! ";
			link.l1 = "... ";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "够了... 我累了。 我被打败了... 请怜悯不幸的杰西卡的命运吧! ";
			link.l1 = "当然... 我会让你可怜的灵魂从这具尸体的重担中解脱! ";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // 听过杰西卡的故事
			{
				link.l2 = "我知道你的故事, 杰西卡。 我很抱歉你的人生如此悲伤并以那样的方式结束。 你想和我谈谈, 对吗? 好吧, 我会试着忘记你最近试图杀我, 我会听你说, 尽管这对我来说并不容易... ";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);// 允许军官进入
		break;
		
		case "exit_talk":
			dialog.text = "谢谢你... 你已经知道Beatrice Sharp和劳伦斯... 我的劳伦斯。 我毫不犹豫地杀了她, 但我杀不了他。 我做不到, 但他可以。 杰西卡死了... ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... 但血誓, 由可怕的誓言束缚, 仍未履行。 这个誓言的力量来自印第安魔法, 它让尸体从坟墓中站起。 \n仇恨把我的灵魂变成了沙漠。 每个来到这个暗礁的人都被我杀死, 他们的尸体成为我的傀儡。 我只能向击败我的人请求帮助... ";
			link.l1 = "我能为你做什么? 我唯一能做的就是让你从这具尸体的痛苦中解脱... ";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "帮助我... 带我去找他。 ";
			link.l1 = "去找劳伦斯.贝尔特罗普? 我该怎么做? 我的船员要么一见到你就跑, 要么会毫不犹豫地烧死你。 顺便说一句, 你仍然能屠杀我的人并‘控制’他们... ";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "他们不会看到我, 但你会。 你一定已经明白我拥有生者无法拥有的力量。 但没有你的允许, 我无法登上你的船。 带我去找他。 \n我不会在你身边待太久, 也不会伤害你的人。 在牙买加的波特兰峡午夜让我上岸, 第二天晚上我们再见面, 你会得到你想在这里找到的东西。 ";
			link.l1 = "你怎么知道我为什么来这里? ";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "我知道很多, 比生者知道的还多。 我看到了她... 你需要一份给她的文件, 你会得到的。 你会得到更多, 我会额外给你一些东西。 带我去找他... ";
			link.l1 = "哼。 我不喜欢你对海伦的嗜血意图。 别碰她。 毕竟, 她不应该为她母亲的行为负责。 ";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "你打败了我。 我不会伤害她... 我保证。 ";
			link.l1 = "还没完呢。 你打算解除你给我下的众多诅咒吗? 我承认, 我不喜欢永远带着它们生活的想法... ";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "没那么简单... 等我们在波特兰峡见面后, 我会告诉你如何治愈自己。 ";
			link.l1 = "等你什么? ... 你是什么意思? ";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "等我和他见面之后。 ";
			link.l1 = "哦, 他不会高兴的。 我能想象。 好吧, 总结一下: 第一, 你承诺没人会看到你; 第二, 你不会伤害我的船员; 第三, 你连海伦的念头都不能有; 第四, 你会给我我要找的东西; 第五, 你会治愈我的诅咒。 对吗? ";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "差不多。 我不会治愈你, 但我会告诉你怎么做。 你得自己来。 ";
			link.l1 = "好吧。 成交。 我允许你登上我的船。 ";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "嘿! 你在哪? 就这样消失了... ";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;// 打开地点
			DeleteAttribute(pchar, "GenQuest.CannotWait");// 可以加速时间
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // 负面效果属性
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);// 允许军官进入
			LAi_LocationDisableOfficersGen("shore36", true);// 禁止军官进入波特兰峡
		break;
		
		case "shore":
			dialog.text = "你遵守了诺言 --我们到牙买加了。 明天晚上来这里, 我会履行我的承诺。 再见。 ";
			link.l1 = "再见... ";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// 允许战斗
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "结束了, "+pchar.name+"... ";
			link.l1 = "你是什么意思? ";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "结束了... 拿着, 这是你在找的东西。 这是我对手的信, 和她一起下葬的。 保存得很好。 我已经原谅了她, 我心中不再有仇恨。 ";
			link.l1 = "你... 见到他了吗? 和劳伦斯? ";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // 给予信件
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "是的。 他生命中最后感受到的是恐惧。 我不觉得抱歉。 ";
			link.l1 = "愿上帝原谅他有罪的灵魂... 看来我永远见不到他了。 ";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "你没有失去任何有价值的东西。 他是个非常坏的人。 现在, 我们该道别了, 我在这里没有什么可做的了。 我的誓言已履行, 魔法也失去了力量。 我答应过你一份礼物。 给你。 这是我的焰形大剑。 我不再需要它了。 这把剑独一无二, 世界上找不到更好的。 ";
			link.l1 = "谢谢... ";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "现在说说你。 去布里奇敦的当地教堂, 解除我的诅咒。 你会在那里找到一位神父, 他认识我。 和他谈谈, 他会告诉你怎么做。 准备二十支蜡烛, 你会需要它们。 ";
			link.l1 = "你确定他会治愈我吗? ";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "你要自己做。 上帝会指引你。 放心, 一切都会好的。 ";
			link.l1 = "好的, 我会立即航行到巴巴多斯。 现在呢? ";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "现在我还有最后一个愿望。 把我的身体埋在这个海边的海湾。 我想要这样。 也许有一天你会来看看可怜的杰西卡的坟墓。 再见, "+pchar.name+", 为我祈祷... ";
			link.l1 = "杰西? ..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// 移除贝尔特罗普
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // 贝尔特罗普已死
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // 可以出售这页日记 270912 
		break;
		
		case "soul":
			dialog.text = "你认出我了吗, 船长? ";
			link.l1 = "是... 是你吗? 但怎么会? ";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "是的, "+pchar.name+", 是我, 是杰西卡! 至少是二十年前的样子。 ";
			link.l1 = "那么... 我死了吗? 但什么时候? 怎么死的? ";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "你没死, "+pchar.name+"。 你现在在布里奇敦的教堂里。 你只是... 在睡觉。 ";
			link.l1 = "这只是个梦吗? 事情看起来太真实了... ";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "有时会发生这种事, "+pchar.name+"。 上帝听到了你的祈祷。 你的祈祷不仅治愈了自己, 也净化了我的灵魂。 非常感谢你, "+pchar.name+"! 我想请求你原谅我在暗礁上的所作所为。 只是... 请原谅我。 我不能不请求你的原谅就离开。 ";
			link.l1 = "我原谅你, 杰西卡。 我真的还活着吗? ";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "你活着... 别担心。 很快你就会醒来。 我只是想道别。 ";
			link.l1 = "你真的很... 美丽! ";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "你喜欢我吗? 是的, 曾经有一段时间, 小安的列斯群岛最好的求婚者都在追求我, 特索罗岛每三个海盗中就有一个准备为我决斗。 ";
			link.l1 = "但你只需要一个... 呃, 姜黄色的护身符! 告诉我, 你为什么会变成这样? ";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "因为我的愤怒, 因为我的仇恨, 因为我无法理解。 原谅和忘记。 我本可以开始新生活, 但我宁愿投身于愚蠢而无意义的复仇。 是你释放了我。 谢谢你, "+pchar.name+"... ";
			link.l1 = "我为你的人生感到难过... ";
			link.l1.go = "soul_7";
		break;
		
		// 这里检查玛丽
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // 玛丽是军官
				dialog.text = "别... 你还有你的姜黄色护身符... ";
				link.l1 = "我的什么? ";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // 玛丽留在岛上
				dialog.text = "别... 你还有你的姜黄色护身符... ";
				link.l1 = "我的什么? ";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "别... 考虑一下我悲伤的经历, 不要重复我的错误。 也不要让你爱的人犯同样的错误。 ";
			link.l1 = "我会考虑的, 我肯定不会犯同样的错误... ";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "想一想。 她在你的船上。 ";
			link.l1 = "玛丽? ! ";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "是的。 她是你生命中能拥有的最好的人。 记住这一点。 她的爱是纯洁的, 她的忠诚是无限的。 她勇敢。 年轻, 但绝望且缺乏经验。 她不懂很多事。 照顾她, 保护她, 不要让任何人站在你们之间。 她是你的护身符... ";
			link.l1 = "我... 我永远不会离开她, 并会保护她免受任何危险。 ";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "她在那个由沉船组成的奇怪岛上... 她在那里不是一个人, 但她很孤独。 她的每个早晨都从想你开始, 每一天都为你祈祷, 每个夜晚她的船舱里都有灯光, 她的枕头因泪水而湿润... ";
			link.l1 = "玛丽... ";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "你们之间有一个女儿。 是那个曾经站在我和劳伦斯之间的女人的女儿。 你的护身符的命运在你手中。 她们不能共存, 就像我和Beatrice不能共存一样。 ";
			link.l1 = "你怎么知道? ";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "彼岸... 能看到很多... 这是你的选择, 但记住: 玛丽是你生命中能拥有的最好的人。 她的爱是纯洁的, 她的忠诚是无限的。 她勇敢。 年轻, 但绝望且缺乏经验。 她不懂很多事。 她需要你的保护。 关心和爱。 她是你的护身符。 ";
			link.l1 = "我会考虑的。 我肯定会那样做... ";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "至于Beatrice的女儿, 知道吗, 你为她所做的高尚行为将被忽视。 很快你就会明白。 小心对待她。 好吧... \n";
			dialog.text = ""+sTemp+"我得走了。 是时候说再见了... 这次是真的。 别忘了杰西卡, 试着偶尔去看看她的坟墓... 只有你知道它在哪里。 ";
			link.l1 = "当然, 杰西。 我会去看的, 我会为你祈祷。 ";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "谢谢你。 再见, "+pchar.name+"! 再见! ";
			link.l1 = "再见, 杰西卡... ";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}