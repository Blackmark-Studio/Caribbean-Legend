// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件は何でしょうか？"),"つい最近もその質問を私にしようとしましたね…","ああ、当ててみようか……また同じところをぐるぐる回ってるんじゃねえか？","聞きなさい、ここで財務を担当しているのは私です、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこに行っちまったんだ…","お察しの通りです、申し訳ありません……","承知しました…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "これらのイヤリングをご覧ください、旦那。ジャングルで盗賊のポケットから見つけたものです。 これは明らかに腕の良い宝石職人の作で、この辺境のものではないと確信しています。いかがでしょうか？";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "フォルケ・デルックという名の債務者がいることは存じております。\n彼の…滞納状況はどれほど悪いのか、教えていただけますか？";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "フォルケ・デリュックの借金の件で来ました。";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "ご依頼は完了しました、旦那。こちらが……あなたのスペイン人の友人です。";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "「…の件で参りました」";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "40ドゥブロン持ってきましたか？";
				if (PCharDublonsTotal() >= 40)
				{
					link.l1 = "「こちらが私の部下のためのお金です…」";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "いいえ、まだ考え中です。";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "「それについてなぜ気にされるのですか、お伺いしてもよろしいでしょうか？」";
			link.l1 = "この男には自由になってもらいたい、牢に入れておくわけにはいかない。そして私の知る限り、 この借金があなたに返済されるまで、彼は解放されないそうだ。この借金を返済することに興味がある。";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "ああ、それは話が変わってくるな。俺も自分の金を取り戻すことには興味がある……このフォルケ・デルックという男は変わり者だ。借りた額は比較的小さくて、五千ペソだった。だが、返済を頑なに拒み、 姿を隠し始めた。結局、利息が元金と同額に膨れ上がり、奴は牢屋に入る羽目になったんだ。";
			link.l1 = "つまり、彼の借金は現在一万にまで膨れ上がっているということですか？";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "ちょうど一万四百五十ペソでございます、旦那。つまり、彼の自由はこの金額ということになります。 私にこの額を支払うおつもりですか？少々驚きました……";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "驚かないでください。こちらがお金です。";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "ふむ……確かに大金ですね。さて、旦那、ひとつ私と取引をしませんか？例えば、あなたが私に任せたい何かがあれば、 私はこの一万五百の価値であなたに恩を売ることもできますが……";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "はい、あなたがこれほどの金額を払うつもりなら、本当にこの船乗りが必要なようですね。\nまあ、私の知ったことではありませんよね、旦那？\nこれが彼の借用証書です。これであなたは彼の借金の権利を得て、彼から金を請求する権利があります。\nそれからもちろん、彼の釈放請願書もございます。";
			link.l1 = "まさに私が望んでいたことです。では、失礼します。 "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "頼みごとか？あいにく、今のところ君に頼みたいことはないよ。";
			link.l1 = "残念だな。それならフォルケに金を持っていくとしよう。じゃあな！";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "頼みごと？ふむ……旦那、もし昨日来ていたら断っていたところですが、今は……ええ、ちょうど片付けてほしいことがあります。ただし、警告しておきますが、かなり危険ですよ。";
			link.l1 = "「何が危険なんだ？」";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "もちろん、あなたの大切な命のためです。だから、同意する前によく考えて、 そのようなことを本当に引き受ける覚悟があるかどうか決めてください。";
			link.l1 = "旦那、危険なんて俺には慣れっこだ。これまでにも何度も危ない目に遭ってきたんだ。\nだから、細かい話に入ろうじゃねえか。要塞の守備隊を一人で全滅させるようなことじゃなけりゃ、 あんたがそれとなく示してることも、俺にできるかもしれねえぜ。";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "よろしい。では聞いてくれ。今夜、数人の海賊と囚人がル・フランソワの海賊の巣を出て、 ル・マランの入り江まで歩いていく。その囚人はスペインの将校で、築城工学の大変な専門家だ。 イギリス人どもは彼を自分たちのために利用するつもりで、軍艦を送り、入り江でその男を引き取るつもりだ。\nその将校は俺の古い友人でな、イギリスの捕虜になってほしくはない。だが、スペインとは戦争中だから、 地元の役人には頼めない。もっと時間があれば、スペイン人――いや、友人を取り戻せる腕利きを雇うところだが、残念ながらそれもできん。\nこの仕事を任せられるのはお前だけだ。ル・マランの入り江へ行き、海賊どもを説得して囚人を引き渡させてくれ。 やつらが素直に応じるとは思えんが、そこはお前次第だ。";
			link.l1 = "護送船団には何人の海賊がいるのでしょうか？";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "わかりません。二人かもしれませんし、三人か四人かもしれません。\nそれで、あなたはどうお考えですか？";
			link.l1 = "「危険なんざ俺には馴染みだ」ともう言っただろう？それに剣のどっちを握るかくらい分かってるさ。";
			link.l1.go = "Sharlie_10";
			link.l2 = "ふむ。おっしゃる通り、危険ですね。私一人で海賊の一味に攻撃などいたしません。";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "それがあなたのご判断です。この仕事に自信がないのであれば、すぐにでもお断りになったほうがよろしいでしょう。 その場合はデリュクの借金返済金をお待ちしております。";
			link.l1 = "わかりました。彼にお金を持っていきます。また後で！";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "承知しました。それは良い知らせですね。それならル・マランの入り江へ行くといい、 海賊たちは午後七時から午前四時までそこにいるはずだ。逃さないように！それから、船を使うなんて考えもするな！ そんなことをしたら奴らは逃げてしまう、必ずジャングルを歩いて行くんだ！\n囚人を見つけたら私のところへ連れてきてくれ、扉は開けておく。街に戻るのは午前一時まで待つことを勧める、 衛兵の目を避ける必要があるからな。気をつけて、幸運を祈る！";
			link.l1 = "ありがとうございます！運が絶対に必要になりますね……";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "ちょっと待て！銃すら持っていないようだな。俺のを一本やるよ。弾もいくつかあるぜ。役に立つと思うぞ。";
			link.l1 = "はい、これは間違いなく役立ちます。ありがとうございます、旦那。";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "さあ行きなさい、神のご加護がありますように！";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "素晴らしい！無事に処理できて、私はとても満足しております。作戦の詳細までは伺わなくてもよろしいのでしょう？\nさて、私の親愛なるスペインのお客様も、これで我が家で安心していただけますね……";
			link.l1 = "フォルケ・デルックの借金はどうなっていますか？";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "もちろんです。彼の借用証書をお受け取りください。これであなたは彼の債務を引き継ぎ、 彼に返済を請求する権利を得ました。さて、もちろん彼の釈放申請も行いました。約束通りすべて済ませましたが、 いかがでしょうか？";
			link.l1 = "はい、旦那。すべて契約通りに厳格に進めております。それでは、これにて失礼いたします。";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "それで、彼の借金を支払う準備はできていますか？";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "はい。こちらが金です。";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "残念ながら、まだ必要な金額を集められておりません……";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "ふむ。確かにおっしゃる通り、これは高価なイヤリングで、間違いなく旧世界で作られたものですね……何と言いましょうか？三十……いや、三十五金ドゥブロンでお譲りしましょう。お金を受け取りなさい、これ以上の値はつきませんよ。";
			link.l1 = "３５ドゥブロン？悪くない値段ですね。承知しました。どうぞ。";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "いいや。このイヤリングは自分で持っておくことにするよ。";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "分かっております、分かっております、船長。 あなたの航海士はほとんどすべてのフランス領植民地で借金を重ねているようですね。実を申しますと、 私はそのことをずっと前から存じております。これは標準的な手続きでして、同業者にも確認を取っておりました……";
			link.l1 = "「そして、前回の取引の際に私に知らせるほど重要だとは思わなかったのですか？」";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "なぜかと申しますと、その時私は主にデリュックの私への借金、ちなみにそれが最大額でしたが、 それに気を取られておりました。\nあなたがその返済を済ませてくださったので、私はすぐに同業者たちへ通知いたしました……我々は多数の専門的な飛脚を抱えておりますので、ほどなくして私の机の上にデリュックの手形が山積みになったのです。 ";
			link.l1 = "なるほど……私が彼に重大な関心を持ち、支払う手段もあると知った上であなたはそれらを買ったのですね……これは恐喝ですよ、モンシニョール。";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "私の仕事ですから、船長！あなたの航海士の本日現在の総借金は40ドゥブロンでございます。しかも、利息も発生しております……お支払いになりますか？";
			link.l1 = "まだ答える準備ができていませんが、検討いたします。さようなら！";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "素晴らしい！次に何をすべきかはご存知ですね、前回と同じです。こちらが書類です――監獄司令官にお渡しください。お取引できて光栄でした、船長。";
			link.l1 = "この状況で楽しめることはほとんどありません。さようなら。";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(40);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
