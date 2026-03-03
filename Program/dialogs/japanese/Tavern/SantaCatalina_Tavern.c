// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("もちろんだ、Helen。どうしたんだ？","ああ、やっと何が欲しかったか思い出したのか？","本当に大丈夫か？お前、ちょっと心配になってきたぜ。医者に診てもらったほうがいいんじゃねえか？ ","よし、ヘレン。少し休んで、外の空気を吸ってこい――つまり、ひと休みするんだ。それから戻ってこい。うん？","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("いや、特に何もないぜ。","いやいや、ご迷惑をかけてすまねえな。","たぶん、お前の言う通りだな……","ああ、たぶんお前の言う通りだ。それが一番いい方法だな。",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),"「少し前に俺に質問しようとしたよな」 "+GetAddress_Form(NPChar)+"...","今日一日で、その質問を持ち出すのはこれで三度目だぞ…","「また何か質問かい？」","ブロック",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "「聞け、」 "+npchar.name+"「ヤン・スヴェンソンって誰だ、どうやってそいつを見つければいいんだ？」";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "聞いてくれ、この町に錬金術師が来ていないか？医者だ。イタリア人で三十歳くらい、 名前はジーノ・グヴィネリっていうんだ。何か聞いてないか？";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "森の悪魔を知らねえ奴に会うのはこれが初めてだぜ。そのあだ名はスペイン人が付けたもんでな、 十五年も前にプロビデンス島のあの私掠船長の首に金貨の袋まるごと懸けたんだ！\nああ、年月はあっという間に過ぎていく……もうみんな、俺たちのヤンのことを忘れかけてる。もしかしたら、本当にあいつも休む時が来たのかもしれねえな。";
			link.l1 = "俺はここに来たばかりで、あまりよく知らねえんだ…";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "もし昔のことに興味があるなら、歴史書を売ってやってもいいぜ。多くの奴らが大金を払う代物だが、俺は……";
			link.l2 = "ごまかすんじゃねえ！質問しただろうが。もう一度聞くぜ、ヤン・スヴェンソンはどこに住んでる？ あいつと大事な話があるんだ。";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "彼は市長邸の向かい、噴水のそばの大邸宅に住んでいるぜ。\nだが今はちょっと厳しい状況らしくてな、どうしても必要ってわけじゃなきゃ、あまり邪魔しない方がいいぜ。";
			link.l1 = "「なんでだ？」";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "彼のお気に入りの娘ヘレン――「ルンバ」とも呼ばれ、亡き親友ショーン・マッカーサーの娘――が行方不明になった。安らかに眠れ、親父さん……ヤンは自分に子供がいないから、その小悪魔みたいな娘を本当の娘のように可愛がっていたんだ。だが、 その娘はスクーナー船『レインボー』と乗組員全員と一緒に消えてしまった\nあの娘が気の毒でならない。滅多にいない美人で、頭も切れる。火のように情熱的で気が強いから「ルンバ」 と呼ばれていたんだ！父親が知っていることは全部教え込んで、船も受け継いだし、 乗組員も誰一人離れずに彼女のそばにいた。年季の入った海の狼たちですら、彼女を船長と認めていたんだ……";
			link.l1 = "女海賊だと？彼女に何があったんだ？";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "誰にも分からねえ……一週間ってのはそんなに長くねえが、マッカーサーの未亡人は娘に何かあったと確信してて、 それをスヴェンソンにも信じ込ませたんだ。奴は部下を呼び集めて自ら捜索を始めたが、今のところ成果はなし。 「レインボー」とその乗組員は跡形もなく消えちまった\nグラディスの居場所を教えてやってもいいぜ、千枚のエイトピースでな。";
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = "あんたの知識はずいぶん高くつくが、興味が湧いたぜ。ほら、金だ。で、彼女はどこにいるんだ？";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "やめとけ。必要なら俺が自分でやるぜ。じゃあな、話を聞かせてくれてありがとな！";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "彼女の家は埠頭のすぐそば、係留所の左側にあるんだ。\nだが、たぶん今は家にいねえよ。あの人は一日中砦の壁のあたりをうろついて、愛しい娘を見張ってるからな。\nもう涙も枯れ果ててるはずだぜ。";
			link.l1 = "話を聞かせてくれてありがとう！じゃあな、相棒！";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("いいや、聞いたことはねえな。薬草師や医者ならいるが、そんな名前のやつはいねえよ。","こんな変わった名前は初めて聞いたぜ。いや、あんたの言うその男が来たことは一度もねえな。","ここには錬金術師なんて一人もいねえよ。医者ならいるが、そんな変な名前の奴はいねえな。");
			link.l1 = "なるほど。残念だな。引き続き探してみるぜ！";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
