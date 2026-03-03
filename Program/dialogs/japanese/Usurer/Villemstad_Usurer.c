// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件を承りますか？"),"つい最近もその質問を私にしようとしましたね……","ああ、さては……また堂々巡りってわけか？","聞きなさい、ここでは私が財務を担当していますので、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ……","そのとおりです、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "旦那、少々変わった用件で参りました。最近、ガイウス・マルシェという名のフランス私掠船長が、 あなたに金の聖体顕示台と金の香炉という二つの珍しい品を売ったことを存じております。その品々 を私に譲っていただきたいのです。";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "ドゥブロン金貨の小箱をお持ちしました。";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "「ああ、そうだ！もちろん覚えているよ！確かにあれは本当に珍しい品で、しかも高価だった。だが、 残念ながら遅かったな、船長。もう手元にはないんだ。すでに売ってしまったよ。」";
			link.l1 = "信じられません！そんな教会用品に興味を持ったのは誰ですか？旦那、誰に売ったのですか？ 私が買い戻せるか試してみたいのですが…";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "ふむ、どうして私の顧客の名前をあなたに教えなければならないのですか？";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "もしかすると、私がマティアス・ベック総督の親しい友人だから、 あなたのために適切な許可を彼に頼めるかもしれませんね？";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "もしかすると、私がオランダ西インド会社と非常に良好な関係を築いており、 諸島の多くのオランダ人入植者たちに大きな支援をしてきたからでしょうか？";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "「俺が払うからじゃねえか？」";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "ああ、確かにその通りだ "+GetFullName(pchar)+"「…総督ご本人のご友人であり、ルーカス・ローデンブルグの犯罪的陰謀を暴いた方ですね…それを忘れるはずがありません。もちろん、お話しします。」";
			link.l1 = "それでは、何でもお聞かせください。";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "ああ、そう、その通りです "+GetFullName(pchar)+"「海賊“幽霊船”の偉大なる征服者か。そんなこと、どうして忘れられようか？もちろん、お話ししますよ。」";
			link.l1 = "それでは、ぜひお聞かせください。";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "よろしいでしょう。金のドゥブロンでいっぱいの箱を用意していただけるなら、 あなたより先に購入した者たちについてお話ししましょう。";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "どうぞ。これらは私にとってとても大切な品なのです…";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "わかった、頼まれたものを持ってくるよ。どれも私にとってとても大切な品なんだ……";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("You've given a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "素晴らしいですね。その場合、いくつか情報をお分けしましょう。";
			link.l1 = "お話をうかがいましょう。";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "金の香炉はロラン・モーゼスという男、通称「キャップのロリー」に買われたんだ。 この肉屋がなぜ貴重な教会の品を欲しがったのか、俺にはさっぱり分からないが、 なぜか彼はそれを手にして言葉にできないほど喜んでいた……\nところで、君がロリー本人に会うことはまずないだろうな。";
			link.l1 = "なぜですか？";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "なぜなら、この熱心なイギリス商人の略奪者が、 最近自分のスクーナーでフォックス大佐の爪の中にまっすぐ飛び込んだからです。\n誰だかご存知ですか？ ";
			link.l1 = "間違いないぜ！アンティグアのセントジョンズにいる「シーフォックス」の司令官だ…";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "そうか、それなら我々が哀れなロランデに二度と会えない理由も分かるだろう。 大佐は彼のスクーナーと生き残った乗組員全員を押収し、セント・ジョーンズへ引き渡した。おそらく、 彼らはもう首に縄をかけられてしまっただろうな。";
			link.l1 = "なるほど。それで、モンストランスは？";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "オステンソリオはごく最近、クマナのベリンダ・デ・リベロ旦那から入手されました。非常に著名な旦那で、 クマナ総督フェルナンド・デ・ビジェガスご本人の親族です。\nおそらく彼女はそれを教会への贈り物として献上したかったのでしょう。";
			link.l1 = "ベリンダ・デ・リベロ夫人か？クマナで会えるんだろうな？";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "間違いなく。彼女自身がウィレムスタッドからまっすぐ家に帰ると言っていた。";
			link.l1 = "「わかりました。ありがとうございます。」 "+npchar.name+"、とても助かりました！";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "いつでもどうぞ、旦那。時々お立ち寄りください！";
			link.l1 = "太っ腹で頭の軽い裕福な客がたくさん来ることを祈ってるぜ……ははっ！";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
