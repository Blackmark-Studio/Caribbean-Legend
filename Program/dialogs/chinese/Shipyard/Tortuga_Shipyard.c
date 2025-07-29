// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题吗? ", "我能为你做些什么? "), "你刚才已经问过我问题了... ", "在我的造船厂或是镇上其他任何地方, 我从未见过如此好奇的人。 ",
                          "问这么多问题做什么? 我的工作是造船, 咱们还是专注于此吧。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性去哪儿了... ",
                      "嗯, 好吧... ", "继续... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "我在找盖乌斯.马沙伊。 我最后一次听说他时, 他把他的大帆船‘圣玛格丽塔号’停靠在这里让你修理... ";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "他自己的大帆船? 嗬嗬, 这可真是个笑话, 船长。 盖乌斯.马沙伊只拥有一艘快要报废的单桅帆船... 他决定成为私掠者后, 作为战利品捕获了一艘大帆船。 幸运的家伙, 第一次突袭就得到了这样的战利品\n我出了大价钱买那艘大帆船, 但他拒绝了, 你能想象吗! 相反, 他把他那可怜的单桅帆船贱卖了, 用卖得的钱来修理大帆船! 换新帆。 涂新漆。 改新名字 —通常这不是什么好兆头\n当然, 原来的名字太天主教了, 但我女儿也叫玛格丽塔, 所以我觉得这名字终究还算合适... 他说他受够了暴力, 打算转行做商人。 而且他运气真好... ";
			link.l1 = "我想, 经商应该比较安稳, 但天主教的大帆船通常不会被单桅帆船捕获。 他的船现在改名叫什么了? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "‘令人钦佩号’... 这不足为奇! 他当时围着他的新大帆船打转, 就像在追求新娘一样, 不停地欣赏着她。 ";
			link.l1 = "我明白了。 盖乌斯现在在托尔图加吗? ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "不在。 他驾驶新船出航了, 到现在还没返回托尔图加岛。 我不知道他当时的航向, 所以在这件事上帮不了你。 ";
			link.l1 = "真麻烦... 我真的很需要他。 我们甚至应该为他的‘令人钦佩号’喝上一杯。 不管怎样, 谢谢你提供的信息。 ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "哦, 不客气。 船长, 欢迎再次光临。 如果你的船需要修理, 随时都可以来, 我们这儿总有空位! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}