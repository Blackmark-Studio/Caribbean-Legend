// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「少し前に俺に質問しようとしたよな」 "+GetAddress_Form(NPChar)+"...","今日一日で、この質問を持ち出すのはこれで三度目だぞ…","「また質問かい？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "「聞け、」 "+npchar.name+"、ミゲル・ディチョソという男について何か聞いたことがあるか？ やつの船がイスラ・テソロの海域で目撃されたって話だが……";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "「聞け、」 "+npchar.name+"最近、イスラ・テソロでミゲル・ディチョソを見かけてないか？";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "ああ、あるぜ。あのスペインのドンが、シャーク・ドッドソンにすごい船――フリゲート艦を売ったんだ、まだここに住んでた頃にな。ああ、あの船よ……とんでもねえ代物だったぜ……";
			link.l1 = "当ててみようか。あの女は今風で流線型の船体を持ち、十六ノットも出せたんだろ？それで名前は『サンタ・キタリア』 だったんじゃねえか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "船体と速さについてはまったくその通りだが、あの船の名前は違ったんだ――『サン・マルティン』ってな。シャークはあの船を手に入れるために、あの悪党に山ほど金貨を払ったのさ。";
			link.l1 = "「本当に『サン・マルティン』で、『サンタ・キテリア』じゃなかったのか？\nいつそれを買ったんだ？\nそれと、なぜディチョソを悪党呼ばわりしたんだ？」";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "畜生め、間違いなくあれは「サン・マルティン」だったぜ。なぜなら俺自身が、 アレクサスの手下どもがあのカトリックのたわごとが書かれた銘板を船尾から引き剥がすのをこの目で見たからな。 シャーク・ドッドソンはあの船を「フォーチュン」と名付けた。あんな美しい船にはぴったりの名前だ。（ぺっ） あいつは54年の冬、ブレイズが殺される少し前にその船を手に入れたんだ\nなぜドン・ミゲルを悪党呼ばわりしたかって？あいつがその忌々 しい船をプロビデンスでスペイン海軍から盗みやがったからさ！ ドッドソンはサン・フアンの砦と守備隊を煙と炎で騙す大芝居を打ったんだ。酔っ払うといつも俺に自慢してたぜ。 シャークは損傷したラガー船を二隻犠牲にして、フリゲートとの戦いを本物に見せかけたんだ\n夜になると、こっそり「サン・マルティン」をイスラ・テソロへ回航した。シャークは船を、 ディチョソは金を手に入れたってわけさ。あのずる賢い野郎は後になって上官に、 フリゲートは海賊艦隊との戦いで沈んだと報告しやがったし、サン・フアンの砦の司令官もそれを裏付けたんだ。";
			link.l1 = "おお、あのスペインのドンどもは本当に懐を肥やしてやがるな！まったく抜け目ねえ野郎だぜ！なあ、本当にそれは1654年の冬に起こったことか？春だったってことはねえのか？それに、 あのフリゲート艦は嵐で傷んでる様子を見せなかったのか？";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "たしか冬だったと思うが……ああ、どうだろうな。もしかしたら春だったかもしれねえ。はっきりとは覚えてねえんだ。 たぶん酔っぱらってたんだろうよ。フリゲート艦はまったく傷んでなかった、ピカピカの新造船だったぜ。";
			link.l1 = "「で、あの見事なフリゲート艦は今どこにあるんだ？」";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "闇深い話だぜ……ブレイズが殺されたとき、誰もがシャークを疑ったんだ。なぜなら、シャークのネックレス――サメの歯――が死体の上で見つかったからな。しかも、その夜シャークがブレイズの家にいたのを見た奴もいたんだ\nシャークは黒印を押される前にイスラ・テソロから逃げ出した。ダーク・パスターのもとを訪ねて、 自分のフリゲート艦をブリッグと交換したらしい。今どこにいるかは誰にも分からねえ。 ザカリーがそのフリゲート艦を後でウィリアム・パターソンに売ったんだ。";
			link.l1 = "このパターソンって誰だ？";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "なんだ、ウィリー・パターソンを知らねえのか？あいつはスコットランド野郎で、カリブに来たばかりだぜ。 自分を王立艦隊の船長気取りでな、フォックス大佐のお気に入りさ！ちなみに、 最近はジャックマンとも取引を始めたらしいぜ。パターソンの旗艦は『フォーチュン』そのものだ。";
			link.l1 = "なるほどな。今ディチョソがどこにいるか知ってるか？";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "さっぱり分からねえよ。「フォーチュン」とのあのいざこざの後、あいつはテソロ島で見かけてねえし、 噂も何も聞いちゃいねえんだ。";
			link.l1 = "「よし、」 "+npchar.name+"、詳しい情報をありがとう！あんたは最高の酒場の主人だぜ！あんたみたいな人がもっといればいいのにな……じゃあな！";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "「幸運を祈るぜ」 "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "どうやらお前ら二人はお互いを追いかけっこしてるみたいだな、相棒。ああ、ディチョソはここにいたぜ、 まさにお前が立ってるその場所にな。しかも全く同じように、お前がシャープタウンに来た時、 あいつもお前のことを聞いてたんだ。";
			link.l1 = "くそっ！それがニュースか……で、今ミゲルはどこにいるんだ？";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "俺にはわからねえ。あいつは海に出ていったが……ブルーウェルドのことを何か言ってたぜ。たぶんお前を探しにそこへ行ったんだろうな。";
			link.l1 = "お前があいつをブルーウェルドに送り込んだ張本人か？";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "いや、俺が言ったのは、あんたに長いこと会ってないってだけだ。";
			link.l1 = "なるほど。よし、わかった。ありがとな、相棒！";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
