// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「何だ、」 "+GetAddress_Form(NPChar)+"...","もうこれで三度目だぞ、俺にちょっかい出すのは…","「また質問かい？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "俺の昔の仲間フェルナン・リュックを探してるんだ。あいつにちょっと聞きたいことがあってな。1週間前にここでずいぶん騒いだって聞いたんだが…";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "俺の友達とここで会う約束をしたんだが、どこにも見当たらねえんだ。あんた、どこに行ったか知らねえか？ まだ町にいるのか、それともせめて島にはいるのか？名前はロングウェイって言う、中国人だ。";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l2 = "「良い知らせだ」 "+npchar.name+"。お前さんの窮地を救う品がちょうどあるぜ。極上のワイン百本とラム酒百本だ。こんな積荷があれば、 客どもはまた酒の川で泳げるってもんさ。支払う覚悟はできてるか？";
				link.l2.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l2 = "「さて、」 "+npchar.name+"、取引の条件について話し合う準備はできてるか？";
				link.l2.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l2 = "「それで、」 "+npchar.name+"。こちらはすべて手配済みで、品物はすでに酒場へ向かっているぜ。支払いに進もうか？";
				link.l2.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "地獄でもまだ楽しんでるかもしれねえな。お前の仲間はもう死んじまったから、ちょっと遅かったな、船長。 あそこの一番奥のテーブルに座ってる男が葬式代を払ったんだが、どうもそいつが原因を作った張本人って気がするぜ。 吊るされそうな面構えってやつだ。名前はロバート・マルテンだ。気が向いたら、自分で行って話を聞いてみな。\n ";
			link.l1 = "ありがとうよ、相棒。ロベール旦那と話してくるぜ。 かわいそうなルック爺さんの魂の安らぎのために一杯やろうじゃねえか…";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "話すことなんてあるか？あいつがあんたと仲間を襲って、あんたたちがやり返したんだろ。こんなの、 ほとんど毎日のことだぜ。よくやった。さて、あとは俺が後始末をしなきゃな……";
			Link.l1 = "お前が片付けるんだろ、もう慣れてるはずだぜ。あいつについて何か知ってるか？";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "大したことはないさ。あいつは数日前に現れたんだ。ここが気に入ったみたいで、町外れに家まで借りてたよ。 よく来てたし、支払いもちゃんとしてた。何より、この間ずっと礼儀正しくしてて、誰にも悪口なんて言わなかったんだ。 お前とお仲間を襲ったって聞いて、今でも信じられねえよ。ここに腰を据えるつもりなんじゃないかと思ってたくらいだ。 ";
			Link.l1 = "ある意味では、そうしたんだ。まあ、大したことじゃねえが、ありがとな、相棒。また会おうぜ。";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_BasTerTavern_3");
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "その名前には心当たりがねえし、基本的にああいう奴らは俺の店に入れねえし、興味も持たねえんだ。";
			Link.l1 = "なるほどな。よし、また後で会おうぜ。";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "「ああ、」 "+GetAddress_Form(NPChar)+"、それどころじゃねえんだ。アンティグアから仕入れてた奴が蒸留所を失っちまった――海賊どもに襲われて、すべて焼き払われたんだ。今じゃ、ラムもワインも少なくとも二ヶ月は入らねえってさ。";
			link.l1 = "だったら新しい仕入れ先を探せよ。まさか二ヶ月もただ待ってるつもりじゃねえだろうな？";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "信頼できる仕入れ先を見つけるのは簡単じゃねえ。\n小さな商人と取引してみたが、あいつらは当てにならねえんだ。\n品物が届く時もあれば、届かねえ時もある。\nだが、大きな仕入れ先なら全てが時計のようにきっちりしてる――安定した納品と高品質だぜ。";
			link.l1 = "そうだな、普通の仕入れ先に問題があるなら、闇の世界で誰かを探してみたらどうだ？あいつらはめったに裏切らねえし、 品物もいつも揃ってるぜ。";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "「わかってるだろう」 "+GetAddress_Form(NPChar)+"、この酒場はいま世間の目が厳しいんだ。役人と揉め事はごめんだぜ。もし評判のいい奴が品を持ってきたんなら、 一山買うどころか、どこから来たかなんて見て見ぬふりもしてやるさ\nだが、こんな切羽詰まった状況じゃ、細かいことなんざ誰も気にしねえだろ？大事なのは疑われないことだ。 だが長い目で見りゃ、俺が相手にするのは真面目で誠実な商人だけだぜ。";
			link.l1 = "わかったぜ。まあ、また後で寄るかもしれねえ。どんな問題も、うまくやれば解決できるもんさ。";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "船長、こりゃあ信じられねえぜ！どうやってこんなことをやったんだ？まあ、細けえことはいい。で、 こんな豪華な酒の積荷と引き換えに何が欲しいんだ？それと、書類の方はちゃんと問題ねえのか？";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "書類かい？もちろん全部ちゃんと揃ってるぜ。まさか本当に確認するつもりじゃねえだろうな？";
				link.l1.go = "TPZ_Tavern2_2";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				link.l1 = "「書類仕事か？」";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				Notification_Reputation(false, 40, "low");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "船長、どうかご理解ください。この酒の荷はどうしても手に入れたいんです。しかし、 俺の自由と評判も同じくらい大事なんだ。総督は闇商人に容赦しねえ、どんな小物でもな。もしあんたの評判が良けりゃ、 書類がなくても目をつぶれたが、今は……あんた、目立ちすぎてるんだよ……";
			link.l1 = "善行をする時が来たようだな。待ってろ、すぐ戻るぜ。";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "今回はお前の言葉を信じてやるぜ。で、その品をいくらで売るつもりだ？";
			link.l1 = "ワイン10本ごとに30ドゥブロン、ラム10本ごとに5ドゥブロン欲しいんだ。\n全部まとめて――各100本ずつなら、合計で350ドゥブロンになるぜ。";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "待てよ、船長！そりゃあ昼間強盗じゃねえか！確かに俺の状況は切羽詰まってるが、赤字で商売なんてできねえよ！";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "もしかしたら割引してやってもいいぜ。\nだが、それだけじゃねえ。俺はあんたの専属の仕入れ人になりてえんだ。確実で迅速な納品を保証するぜ。 バステールに倉庫を借りて、そこから直接品物を届けるから、遅れは絶対にねえ。酒も常に十分に蓄えておくから、 品切れの心配もいらねえ。割引込みで、値段は二百四十ドゥブロンだ。どうだ？";
				link.l1.go = "TPZ_Tavern2_4";
				Notification_Skill(true, 50, SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "よし、取引ごとに二百四十ドゥブロンまで値下げしてやるぜ――長い付き合いを考えてるからな。今後はお前さんの要望に全部応えて、安定した供給も約束するぜ。どうだ？";
				link.l1.go = "TPZ_Tavern2_7";
				Notification_Skill(false, 50, SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "それでも昔払ってた額より高いな。だが、もう学んだからな――安定にはそれだけの価値がある。お前の条件を飲むぜ、だが覚えておけ、 一度でもしくじったら他の仕入れ先を探すからな。俺が余分に払う理由をちゃんと説明してもらおうか。もう一つ聞くが――役人どもへの対処はどうするつもりだ？";
			link.l1 = "今すぐそれに取りかかるぜ。全部片付いたら、品物を持って戻ってくるからな。";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "どうかご遠慮なく。客のジョッキがまた酒で満たされるのが待ちきれねえんだ。";
			link.l1 = "心配するな、待たせたりしねえよ。";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "まだ高すぎるぜ、船長。この値段は前の仕入れ先に払ってたよりも高いんだ。今は同意したとしても、 数か月もすれば生産が再開して、またあいつのところに戻ることになるだろう。わざわざ高い金を払う理由なんてねえよ。 ";
			link.l1 = "分かった。よし、俺の最終提案だ――二百ドゥブロンだぜ。これで納得できねえなら、この話はここで終わりだな。";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "よし、決まりだ。二百で手を打とう。だが教えてくれ、島の役人たちにはどう対処するつもりだ？前にも言ったが、 総督は密輸に目を光らせてるんだぜ。あいつの目の前で取引なんざ、絶対に見逃さねえぞ。";
			link.l1 = "ははは、まあ、それには異論があるぜ。だが安心しな、役所の面倒ごとはちゃっちゃと片付けるつもりだ。";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "どうかご遠慮なく。早く客たちのジョッキがまた酒で満たされるのを見たいんだよ。";
			link.l1 = "心配するな、待たせたりしねえよ。";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "もちろんだぜ、船長！それで、その積み荷はいくらで売りたいんだ？";
				link.l1 = "ワイン10本ごとにドゥブロン金貨30枚、ラム酒10本ごとにドゥブロン金貨5枚だ。\n全部でそれぞれ100本ずつなら、合計でドゥブロン金貨350枚になるぜ。";
				link.l1.go = "TPZ_Tavern2_3";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				dialog.text = "申し訳ありません、船長。でも、あなたの評判はまだまだ物足りないですね。";
				link.l1 = "くそっ……";
				link.l1.go = "exit";
				Notification_Reputation(false, 40, "low");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "もちろんですよ、船長、もちろん！約束通り240ドゥブロンです。さあ、どうぞ！";
				link.l1 = "取引できて嬉しいぜ！これでまた酒場がラムとワインで溢れるってもんだ。";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "もちろんですよ、船長、もちろん！約束通り200ドゥブロンです。さあ、どうぞ！";
				link.l1 = "取引できて嬉しいぜ！これでまた酒場がラムとワインで溢れるってもんだ。";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "あんたは俺の救世主だぜ、船長！これからも二週間ごとに同じ荷を期待してるからな。約束はきっちり守ってくれよ。 あんな品切れがまた続いたら、俺の酒場はもたねえ……";
			link.l1 = "「心配いらねえ」 "+npchar.name+"。俺の代理人はこの町のクリスチャン・デルースだ。あいつがいれば、 お前の酒場からワインもラムも絶対に切らせねえよ。";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "クリスチャンか？あいつなら知ってるぜ。責任感のある男だ、まあ……いや、なんでもねえ。お上と話がついたなら、あいつを信用してもいいだろう。";
			link.l1 = "素晴らしい。では、失礼する。この町でまだ片付ける用事があるんだ。";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "もっとちょくちょく来てくれよ！";
			link.l1 = "もちろんそうするぜ。";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
