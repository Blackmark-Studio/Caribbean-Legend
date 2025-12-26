// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "俺たちに話すことなんてねえ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","「白い女インディアン」")+" 話がしたいのか？","またお前か。 "+GetSexPhrase("Paleface","「白い女インディアン」")+".",""+GetSexPhrase("白人はよくしゃべるな。まるで女みたいだぜ。","白人女はおしゃべりが好きだな。")+"","精霊が俺の青白い顔をここに運んだ "+GetSexPhrase("兄弟","姉妹")+" 私に。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「ああ。」","ああ、また俺だ。","とても詩的だな。","私もあなたに会えて嬉しいです。",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "なあ、どうして来たんだ、色白の顔したやつよ？";
			link.l1 = "ああ、別に何もないさ、ただお前の話を聞きたかっただけだ……";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("白人が話したいのか？","またお前か、色白野郎？","「色白野郎はおしゃべりが好きだ。」","精霊が俺の色白の兄弟を俺のもとに連れてきたんだ。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ああ。","「ああ、また俺だ。」","とても詩的だな。","私もあなたに会えて嬉しいよ。",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" 「お前の話を聞こう、海の息子よ。」","何の用だ "+npchar.name+"、色白野郎か？","見知らぬ者よ、お前の話を聞こうじゃねえか。");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("お前に渡すものがあるんだ。見てみるか？","本当に面白いものを見てみたくないか？きっと気に入るぜ…","ジャングルの子よ、お前が喜びそうなものがあるんだ。見てみたいか？");
				link.l1.go = "gift";
			}
			link.l9 = "ああ、別に用事はないさ。ただ、お前の話を聞きたかっただけだ……";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" 見たがっている。見せてやれ。",""+npchar.name+" 興味がある。見せてくれ。");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "鏡をくれ。";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "おお！今 "+npchar.name+" 川の水だけじゃなく、自分の姿を見られるわ！親切な方、ありがとうございます！";
			link.l1 = "もちろん、これで好きなだけ自分の顔を眺められるぞ…";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "おお！なんて美しいんだ！この腕輪は "+npchar.name+"？親切な方、ありがとうございます！";
			link.l1 = "その褐色の手にはめてみな、美人さん、きっと見惚れるほど似合うぜ……";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "おお！なんて美しい指輪だ！これは "+npchar.name+"、そうですか？ありがとう、親切な方！";
			link.l1 = "指にはめてみな、仲間たちがみんなうらやましがるぜ…";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "おお！その素晴らしい緑のビーズは "+npchar.name+"？なんて美しいんだ！ありがとう、親切な方！";
			link.l1 = "それを首に飾りなさい、森の娘よ。みんながあなたに見とれるだろう……";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "ああ、なんて美しい緑の指輪だ！これは誰かへの贈り物かい\n "+npchar.name+"？親切な方、ありがとうございます！";
			link.l1 = "「お前の手にぴったりだぜ、かわいこちゃん…」";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "聞きたかった "+npchar.name+" 何か用かい、海の息子よ？";
				link.l1 = "その通りだよ、可愛い子。俺と俺の勇敢な戦士たちはセルバへ行くんだ、山の中のスペイン人の集落にな。 案内人を探してるんだよ。案内してくれる男にも、その奥さんにも、俺は惜しみなく報酬をやるぜ。 俺は財宝をたくさん持ってるんだ。美しい銃、魔法の眼鏡、鏡、首飾り、腕輪、指輪……。もしかして、お前の旦那が俺たちの探してる案内人になれるんじゃないか？";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "海の子よ、ようこそ。私はクムワナ、ロコノ族カメ一族の族長だ。何の用で私の村に来たのだ？";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "お頭、贈り物を持ってきたぜ。見てみな、気に入るはずだ。";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "酋長、あなたの助力をお願いしに来たんだ。スペインの植民地メリダに行きたいんだが、 あんたたちのセリバの山中にあるって聞いた。でも、どうやって行けばいいのかわからなくて困ってるんだ。";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "それはお前にとってはいいことだな、海の息子よ、そこへの道を知らないのはな。あそこへ行くには森を抜けるんだ、 恐れ知らずのカポン族の土地さ。まさにジャガーのような連中だ、オーイェ！ 俺はあのスペイン人の場所には絶対行かねえ。俺たちの民は平和な人々だ、カポンの土地には行かない。 クムワナはお前に助言できねえ。その道はあまりにも危険すぎるんだ。";
			link.l1 = "だが、スペイン人どもはそこへの道を見つけやがった！そして俺はあのカポン野郎どもなんか怖くねえ…";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "しかし、お前は知っておくべきだ。奴らは残酷な連中だ。森で俺の仲間を大勢殺したんだ。クムワナが全部話したぞ。";
			link.l1 = "くそっ……";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "おうい！また会ったな、海の息子よ。クムワナに何の用だ？";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "お頭、土産を持ってきたぜ。見てみな、きっと気に入るはずだ。";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "メリダを見つける希望は、まだ俺の中にある……";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "ロコノ族はいつも良き友を歓迎するんだ。";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "拳銃を贈る。"; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "コンパスを贈り物として渡す。";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "安物の望遠鏡を贈り物として渡す。";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "普通の望遠鏡を贈り物として渡す。"; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "まともな望遠鏡を渡せ。"; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "おおい！なんて見事な白人の武器だ！クムワナはお前の贈り物を受け取るぞ！お前もだ、海の子よ、 クムワナとロコノ族からの贈り物を受け取れ。";
			link.l1 = "ありがとう、親分！..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "おおい！白い顔の者たちの魔法のお守りよ！クムワナがお前の贈り物を受け取るぞ！\nお前もだ、海の子よ、クムワナとロコノの民からの贈り物を受け取れ。";
			link.l1 = "ありがとう、親分！..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "おおい！白い顔の者どもの魔法の筒よ！クムワナはその贈り物を受け取る！お前もだ、海の息子よ、 クムワナとロコノ族からの贈り物を受け取れ。";
			link.l1 = "ありがとう、親分！..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "おーい！白い顔の者たちの魔法の筒よ！クムワナがお前の贈り物を受け取るぞ！お前もだ、海の息子よ、 クムワナとロコノ族からの贈り物を受け取れ。";
			link.l1 = "ありがとう、親分！";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "おおい！色白どもの魔法の筒よ！クムワナがその贈り物、ありがたく受け取るぞ！お前もだ、海の子よ、 クムワナとロコノ族からの贈り物を受け取れ！";
			link.l1 = "ありがとう、親分！..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "「何の用で我らの村に来たんだ、海の息子よ？」";
			link.l1 = "酋長、あなたの助けをお願いしに来ました。スペインの植民地メリダに行きたいのです。 あなた方のセルバの山中にあると聞きましたが、行き方がわかりません。 案内してくれる勇敢な戦士を一人つけていただけませんか？";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "おーい！危ない道だ、危ないぞ。その道は森を抜けて行くんだ、恐れ知らずのカポン族の土地さ。 本物のジャガーみたいな連中だぜ、おーい！俺はあのスペイン人の場所には絶対行かねえ。俺たちの民は平和な者たちだ、 カポンの土地には近寄らねえよ。";
			link.l1 = "どうしてもメリダへ行かねばならないんだ。クムワナ、頼むからお前の部下たちに聞いてくれ、 誰か俺の隊に加わってくれる者はいないか？俺の戦士たちは経験豊富で、武装も十分、悪魔すら恐れねえ。 案内人は必ず守るし、終わったらたっぷり礼もするぜ。";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "よかろう、海の息子よ。戦士たちを集めて、お前の望みを伝えておこう。夜明け後にまた明日会いに来い。";
			link.l1 = "ありがとう、親分！";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "おうい！またお前か、海の息子よ。クムワナに何の用だ？";
			link.l1 = "「まだ何もありませんぜ、親分。」";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " 聞け、クムワナ。俺たち一行はどうしても川を渡って、あの忌々しい小さな町に辿り着く必要があるんだ。 どれほど俺たちにとって重要か、説明させてくれ。";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "俺の猟師たちはすでにお前に知らせてあるはずだが…";
			link.l1 = "何度も同じことを言う必要はないぞ、クムワナ。だが外を見てみろ――そして自分の力を過信するな。スペインの石を求めてここに来た俺の勇敢な部下たちは、 お前の村のあちこちに散らばっている。やつらの我慢もそろそろ限界だ。もしその我慢が完全になくなったらどうなるか――お前は知らない方がいい、信じてくれ。";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "黙って聞け、赤い肌の猿め。俺たちの仲間は、この忌々しいカポン族なんかより遥かに恐ろしいんだ。 今は親切にしてやってるが、騙されるなよ。選択肢は一つだけだ。二十四時間以内に案内役を見つけるか、 さもなければ全員縛り上げて、俺たちの部隊の前を歩かせてジャングルを進ませる。もし間違った道を案内したら、 お前自身が沼で死ぬか、縛られたままカポン族と戦う羽目になるぞ。わかったか？";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "クムワナ、この案内人が必要なんだ。俺たちははるばるここまで来たんだぜ、 全部無駄だったなんて部下たちに言いたくねえんだよ。";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "クムワナがもう言ったが、ロコノの誰も白人と一緒に行きたくないんだ。";
			link.l1 = "「それについて何もできないのか？誰かに直接頼むとか、命令を出すとかさ。結局、お前が親分なんじゃねえのか？」";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "酋長はインディアンを無理やり従わせはしない。酋長は支配し、自分の民のために平和を望んでいる。 インディアンたちは知っている――カポン族はロコノ族が白人を連れてくるのを見張っている。カナイマが彼らの首を取ることになっている。 彼らはロコノ族に復讐しに来るのだ。カポン――殺すために。ロコノ族を捕らえ、奴隷にする。";
			link.l1 = "それで、お前たちの首を取ったのは誰だ？どんな精霊や悪魔がインディオどもをこんな腰抜けの虫けらにしたんだ？まあ、 メリダへの遠征は本当に諦めるしかないかもしれねえな。だがな、酋長、一つ覚えておけ。 俺がロコノ族について何か聞かれたら、必ずこう答える――あいつらは価値のない臆病者の部族だってな。自分たちと同じくらい臆病で目先しか見えねえ支配者に率いられて、 カポング族の記憶だけで顔を恐怖に歪めるような奴だ。お前たちはインディオの間で名誉を得ることも、 俺たち白人の間で尊敬を得ることもできねえぞ。";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "青白い顔の者はインディアンの習慣を知らないんだな……";
			link.l1 = "俺はインディアンたちが誰を臆病者と呼び、誰を勇敢な戦士と呼ぶか、十分に知っている。\nさらばだ、クムワナ。俺の言葉を忘れるな。お前は臆病で目先しか見えぬ支配者だ。";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "なぜこんなふうに脅すんだ？俺たちはあんたのことをいい人だと思ってるのに……";
			link.l1 = "俺はいいんだぜ、お前が協力さえすればな、わかったか？猶予は一日だけだ。信じろ、 俺の手下どもは俺の命令なら何でもやる。俺たちの方が強いんだ。もし疑うなら……お前の女房も娘たちも見たぜ。もう言いたいことは伝わっただろう。";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "なぜこんなふうに脅すんだ？俺たちはあんたのことをいい人だと思ってるのに…";
			link.l1 = "俺は機嫌がいいぜ、お前が協力する限りな、わかったか？猶予は一日だけだ。それとな、 俺の部下は俺の命令なら何でもやる。俺たちの方が強いんだ。もし疑うなら……お前の女房も娘たちも見てるぜ。もう言いたいことは伝わっただろう。";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "クムワナは分かっている、色白の者よ。村にはタゴファという猟師がいる。もしかしたら、 彼が集落まで案内してくれるかもしれん…";
			link.l1 = "二十四時間後に戻るぜ。チャーリー・プリンスはもう何も言うことはねえ、野蛮人。";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "海の息子よ、お前か。クムワナがロコノの戦士たちと話したぞ。";
			link.l1 = "それで？志願者はいるのか？";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "あそこに行ったことのある猟師が何人かいるぜ。だが、奴らはカポングを恐れてるんだ、ジャガーどもが荒れてるからな。 行きたがらねえ、カポングがあんたの部隊を殺すって言ってる。白人は怖がっちゃいねえんだ。\n";
			link.l1 = "俺の戦士たちはあいつらなんかより遥かに強いぜ！\nうちの部隊の一部は一生ジャングルで過ごしてきたんだ！\n俺たちはただの素人じゃねえ！";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "すまないな、海の息子よ。俺の猟師たちは怖がっているんだ、カポングは本当に、本当に危険だからな。";
			link.l1 = "よし、それなら奴らにどうやってそこへ行くのか詳しく説明してもらおうじゃねえか？詳しくな。";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "そこへ行くには川沿いに航海して、ある特定の場所で上陸しなきゃならねえ。間違った場所を選べば、 沼地に迷い込んで死ぬことになるぜ。うちのセルバは危険だらけだ。お前ひとりじゃその場所は見つけられねえよ、 海の息子よ。";
			link.l1 = RandSwear()+"「それで俺はどうすりゃいいんだ？どうやってお前の猟師たちを説得すればいいんだ？」";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "クムワナ、もう何も言うな、海の息子よ。";
			link.l1 = "……わかった……";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "私の夫タゴファは部族一の狩人だ。おーい！ "+npchar.name+" 彼女は夫を誇りに思っている。 "+npchar.name+" よくセルバでタゴファと一緒に行動している。遠くまで行くんだ。 スペイン人の居留地がどこにあるかはタゴファが知っている。";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "タゴファは白人どもがメリダと呼ぶスペインの町への道を知っているか？";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "ほう、ほう……タゴファはスペインの町への行き方を知ってるのか？";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("私の夫はセルバには行かないよ、海の息子さん。魚を捕るんだ。いい漁師さ、オーエイ！ ","あたしの旦那は腕のいい猟師だよ、でもジャングルの奥までは行かないんだ。"),RandPhraseSimple("ジャガーが狩りの最中に旦那を傷つけたんだ。今じゃ村で矢を作って座ってるよ、あーあ！","六つの月前に、三人のカポングが私の夫を襲ったのです。今では彼は村から遠くへ狩りに行かなくなりました。絶対に！ おーえい！"));
				link.l1 = LinkRandPhrase("「残念だな…」","残念だな……","なんて残念だ……"));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "タゴファはこのジャングルで育ったんだ。ここにある木も石も全部知ってるぜ！";
			link.l1 = "もし彼が私たちをそこへ連れて行ってくれたら、あなたとタゴファにたくさんの贈り物をあげよう。宝飾品や武器、 何でも。あなたが欲しいものは何でも。もちろん常識の範囲で、へへ。あなたの旦那とどうやって話せばいい？";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "タゴファは白人とは行かない。タゴファは村に残る。狩りに行け。カポンとは戦うな。";
			link.l1 = "奴はカポンと戦う必要はねえ。奴らを見たらすぐに隠れればいい。戦うのは俺の仲間だけだ。";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "いいや、ヤラナウイ。白い顔の者は決して約束を守らない。白い顔の者が口にした言葉は、すぐに虚空へと消えてしまう。 カポンはタゴファを殺し、それから我らの村へ来てロコノを殺すだろう。";
			link.l1 = "お前はカポンどもだけを気にしていればいいと思ってるのか？大間違いだぜ……";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "ヤハフが白人の中に入るぞ！ハヤミはもうヤラナウイとは話さない。";
			link.l1 = "ほう、ほう……";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "タゴファは一日前に狩りに出かけた。明日、太陽が眠る時に戻ると約束した。\n明日来い、海の子よ。私はタゴファとあの小屋にいる。村に入ったら右に進め。\n彼に、お前と一緒に行くかどうか聞いてみる。";
			link.l1 = "タゴファに一番美しい拳銃を贈ると伝えてくれ。\nそしてお前にはたくさんの宝石をやるぜ。";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "ロコノはヤラナウイを信用しない。ヤラナウイはインディアンを欺き、奴隷にする。だが、ロコノはお前の名を聞いたぞ、 白人よ。俺の信頼はお前のものだ。明日、日没後に来い、海の子よ。あの小屋でタゴファと一緒にいる。 タゴファが一緒に行くかどうか、俺が彼に聞いてみる。";
			link.l1 = "タゴファに俺の最高のピストルをやると伝えてくれ。\nそしてお前には宝石をたんまり用意してあるぜ。";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			Notification_Perk(true, "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "おうい！";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" 海の息子に会えて嬉しいぞ。タゴファが戻ってきた。しかし、カシェーリを飲みすぎて眠っている。起こすな、 タゴファは休んでいる。私が話そう。";
			link.l1 = "「よろしい」 "+npchar.name+"。あなたの旦那がメリダまで案内してくれるのですか？";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "タゴファはあなたの戦士たちをセルバを通ってスペイン人の村まで案内することに同意した。しかし、条件がある……";
			link.l1 = "「どれのことだ？」";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "お前はタゴファをカポンの戦士から守るんだ。タゴファはスペイン人ともカポンとも戦わない。危険に直面したら逃げて、 誰にも見つからない。彼はロコノ族一の猟師だからな。";
			link.l1 = "なるほどな。お前の仲間のことを心配してるんだな、それは当然だ。安心しろ、 カポンどもは俺たちが全部片付けてやるぜ。";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "おうい！タゴファは海の子から贈り物が欲しいぞ：たくさん石を撃てる小さいやつと、一発だけ石を撃てる大きいやつ、 どちらもきれいなものだ。それから、それぞれの銃に弾も欲しい――両手の指の数の三倍分だぞ。";
			link.l1 = "おおっ！あんたの部下は銃の扱いに詳しいんだな、へえ？よし、他には何がある？";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "それに、タゴファは青白い顔の連中から美しい魔法の目を欲しがっているんだ。";
			link.l1 = "望遠鏡か？いいぜ。他に何かあるか？";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "タゴファにはもうない。 "+npchar.name+" きれいなものが欲しいんだ。大きな赤い石がついた金の指輪と、たくさんの緑の石でできたビーズがいいな。 "+npchar.name+"マラカイボのホワイト・メアリーでそれを見た。";
			link.l1 = "ルビーと翡翠のビーズがついた金の指輪か？";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "翡翠じゃねえ。光ってて、白人どもが価値をつけてる代物だ。";
			link.l1 = "エメラルドか？エメラルドのビーズか？";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "おうい！";
			link.l1 = "「へっ、」 "+npchar.name+" 宝石について何か知ってるのか！よし、渡してやる。";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "すべてを持ってきて "+npchar.name+" 一緒に行こう、海の息子よ。それからタゴファが、お前とお前の戦士たちを導くだろう。時間を無駄にするな、 半月後にはタゴファと私は隣村へ向かう。偉大な日となるだろう。さあ、行け、\n "+npchar.name+" 眠りたがっている。";
			link.l1 = "あまり待たせないようにするよ。またな。";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "何を持ってきたんだ "+npchar.name+" それでTagofaが尋ねたのか？";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "はい。すべてご指示どおりです。";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "いいや、まだ取り組んでいるところだ。";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" 海の息子よ、幸せだ。今からあなたを夫と呼ぶわ。彼はあなたと一緒に行く。でも、あなたが約束したことを忘れないで。  "+npchar.name+"!";
			link.l1 = "ああ、ああ、全部覚えているよ。俺があいつをちゃんと守るから、心配すんな。";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "武器をしまえ、色白野郎、さもねえと俺たちが無理やりやらせてやるぞ！";
			link.l1 = LinkRandPhrase("「よし。」","「よし。」","心配するな、しまっておくからな……");
			link.l1.go = "exit";
		break;  

	}
}
