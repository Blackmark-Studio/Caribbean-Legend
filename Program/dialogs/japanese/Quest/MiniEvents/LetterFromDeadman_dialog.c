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
			dialog.text = "何の用だ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "何の用だ、 "+GetSexPhrase("相棒","娘")+"？もしラムをくれるってんなら、断る理由はねえぜ。この忌々しい町をぐるぐる歩き回って、足がもう絡まりそうだ。で、 あんたの名前は何だ？";
			link.l1 = "Captain "+GetFullName(pchar)+"「……お前、『イーグル号』の乗組員じゃねえよな？」";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "そして俺は―― "+GetFullName(npchar)+"。ああ、そうだ、俺は『イーグル』の乗組員だぜ。俺たちの船、気に入ったかい、船長？";
			}
			else
			{
				dialog.text = "船長？ほう、ほう……ゴホン……俺はアントニオ・ヴェレンタだ。そして、そうさ、俺は『イーグル号』の者だ。俺たちの船が気になったのかい、船長？";
			}
			link.l1 = "船は船だ。町をうろついてないで、さっさと乗船したほうがいいぜ――お前の船長はもう雷でも吐きそうな勢いだ。潮が引く前に出港するつもりらしいし、坊主、 どうもお前を待つ気はなさそうだぞ。";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "ちくしょう……分かってる、分かってるさ……だが、この街でまだ片付けてねえ用事があるんだ。おい、船長、ドゥブロン金貨をちょっと稼ぐ気はねえか？";
			link.l1 = "ドゥブロン金貨はいつだって歓迎だぜ。だが、稼ぐのと厄介ごとに巻き込まれるのは別だ。仕事ってのは何だ？ さっさと言えよ。";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "ほら、荷物を降ろしているときに、手紙を見つけちまったんだ。わざと隠されてた感じじゃなくて、 ただ古い樽の間に転がってただけさ。うちのフリュート船は何度も拿捕されてるから、 どこから流れてきたのか見当もつかねえんだよ。";
			link.l1 = "手紙を見つけたんだな、だからどうしたってんだ？";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "これはポルトベロのマリサ・カルデラ宛ての手紙だ。封蝋でしっかり閉じられてる……俺の勘が言ってる、これはただ事じゃねえ。船長かもしれねえし、商人かもしれねえ……だが、俺みたいな普通の水夫宛てじゃねえのは確かだ！ただ、俺には宛先を探す時間がねえ――うちの船長は冗談が通じねえからな。なあ、これを買わねえか？千ペソで譲るぜ。あんたは船長だ、 あのセニョリータを見つけるのも簡単だろう。もしかしたら、金か……それ以外のご褒美がもらえるかもな……分かるだろ？\n";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "そうかい、じゃあお前のマリサを探してやるとするか。どっちにしても、俺は失うものなんてねえ。千ペソ以外はな。 手紙を渡せ。";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "悪いな、相棒。でも他を当たってくれ。手紙を届けるより大事な用があるんだよ。";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "「ほらよ。じゃあ、気をつけてな。」 "+GetSexPhrase("相棒","娘")+"、俺は行かないとな――自分の持ち物が『イーグル』号と一緒に出航しちまったら困るからな。";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "お前は誰だ？何の用だ？";
			link.l1 = "私の名は船長だ "+GetFullName(pchar)+"。マリサ・カルデラを探している。";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "マリサなんて知らねえよ。部屋を間違えたんじゃねえか。今すぐ出ていけ、衛兵を呼ぶ前にな。 呼ばれたらすぐに叩き出されるぜ。";
			link.l1 = "Father "+sld.name+" 彼女の友人だと聞いた。彼女宛の手紙を預かっている。その見た目からして、かなり遅れているようだ。 直接渡したいんだ。";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "ああ、神父様……あの方は誰にでも親切すぎるくらいですが、人を見る目は滅多に誤りません。手紙は私に預けてください。 必ず彼女の元に届けます。";
			link.l1 = "申し訳ありません、セニョリータ。しかし、できれば直接お渡ししたいのです。彼女は、 どうやってこれを手に入れたのか、なぜ到着が遅れたのかについて質問があるかもしれませんので。";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "それで俺がお前の善意を素直に信じると思ってるのか？善人ぶった悪党なんざ山ほど見てきたぜ。手紙を置いていくか、 とっとと立ち去れ。";
			link.l1 = "俺は船長として誓う、君にもマリサにも危害は加えねえ。\nそれに、護衛でも武器の扱いに長けた者でも、誰でもこの場に呼んで構わねえ。\n俺の目的はただ一つ、マリサにこの手紙を直接渡すことだけだ。";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "わかった。明日の夜十一時過ぎに来てくれ。彼女が会うことに同意するとは約束できねえが、 お前の言ったことは全部伝えておくぜ。";
			link.l1 = "俺も行くぜ。すぐに会おうな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "「こんにちは」 "+GetAddress_Form(NPChar)+" "+pchar.lastname+"。俺を探してたんだろ、ここにいるぜ。ドロレスが手紙を預かってるって聞いたが？";
			link.l1 = "ごきげんよう、カルデラ夫人。そうです、こちらをどうぞ。あいにく、 お手元に届くまでずいぶん時間がかかったようですね。";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "ドロレス……これは彼の筆跡だ……ラミロの筆跡だ！";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "「しかし、どうしてそんなことがあり得るんだ？もう二年も経っているんだぞ！」";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" 船長……どうやって手に入れたんだ？どこで見つけたんだ？全部知りたい！頼む、知っていることをすべて教えてくれ。";
			link.l1 = "この手紙はある水夫から私のもとに届いたんだ。彼は自分の船の暗い船倉の隅でこれを見つけて、 直接お前に渡したかったんだが、急いで自分の船に戻らなきゃならなくなった。だから、 私にお前を探してくれと頼んできたんだ。そういうわけで、こうしてここにいる。私が知っているのはそれだけだ……";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "ありがとうございます。 "+GetAddress_Form(NPChar)+"！本当にありがとうございます！どうか、行かないでください。もっとお話ししたいのですが、まず……この手紙を読まなければなりません。";
			link.l1 = "もちろんでございます、Caldera様。ここにおります。";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Twenty minutes passed, Marisa read the letter...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "ドロレス……彼は最後の航海の前にこの手紙を書いたんだ。ベリーズの商人から大量の黒檀を買うチャンスがあったけど、 金が足りなかったって私に伝えたかったんだよ。そのときにこの借金をしたんだ……二百ドゥブロン……そのせいで私は今、心の安らぎを得られないんだ。";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "それで全てが分かった……だが、残念ながら、それでお前の重荷が軽くなるわけじゃねえ。しっかりしろ、マリサ。闇は永遠じゃねえし、 この借金もいつまでもお前を苦しめやしねえさ。";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "いいや、ドロレス、そんなことはない！ラミロが隠し財産を残してるって書いてた……あの場所に。まだ誰にも手を付けられてなければ、この借金を返して、この悪夢からやっと抜け出せるかもしれない。";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "主があなたに慈悲をお示しになった！我々の祈りをお聞き届けくださったのだ……";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "船長、改めて、この手紙を届けてくださりありがとうございます。私にとって本当に大切なものです……ですが、もう一つだけお願いがあります。ご存知の通り、夫のラミロは私の全てでした。 他の男性の庇護を求めたこともありません。今、彼がいなくなってしまい、私には頼れる家族も誰もいません\n彼の隠れ家に行かなければなりません――それは町の外にあります。でも、一人で行くのが怖いのです。亡き夫の借金取りが私を狙っていますから。 あなたは手紙を届けるために私を探し、立派に行動してくださいました……どうか、もう一度だけ助けてください。";
			link.l1 = "もちろんだ、マリサ、俺が護衛してやるぜ。いつ出発したいんだ？";
			link.l1.go = "Marisa_16";
			link.l2 = "申し訳ありません、奥様、ですが私がこの町に滞在しているのはもう十分長くなりました。 田舎を散歩するつもりはありません。";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "わかった……あなたはもう、私が望んだ以上のことをしてくれた。ありがとう、船長、そしてお別れだ。";
			link.l1 = "さようなら。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "ありがとうございます、船長。明日の夜明け、七時までに来てください。準備しておきます。";
			link.l1 = "それでは、また会う日まで、奥さん。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "旦那、ここにいらっしゃいましたか……あなたは本当に名誉あるお方です！さあ、出発しましょう。我々の道はジャングルを抜けて、 モスキート湾の近くにある洞窟へと続いています。";
				}
				else
				{
					dialog.text = "船長、やっと来てくれたか……来ると信じていたぜ。あんたみたいに自分の船を指揮する女に会うのは、これが初めてだ。だがもう分かる――あんたは名誉も気高さも、どんな男にも劣らねえ！";
				}
				link.l1 = "素晴らしいですな、奥方。では、時間を無駄にせずにいきましょう。すぐそばにいて、絶対に離れないでください。";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "ありがとう、マリサ。私の父は船長であり、名誉を重んじる男だった――そして幼い頃から、同じ理想を私にも教え込んでくれたんだ。";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "夜明けに来い、七時までにな。準備しておくぜ。";
				link.l1 = "それじゃあな、奥さん。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "そうなのか？あいつも俺のラミロと同じ運命を辿ったのか？";
			link.l1 = "きっと彼は、剣を手にして最期を迎えるか、嵐のただ中で果てることを望んでいただろう。しかし運命は別の道を選んだ――誰にも語らなかった病に倒れ、命を落としたのだ。";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "「ご愁傷様です」 "+pchar.name+" 主は我らの中で最も優れた者をお召しになる……。\nなぜなのか、我々には常に理解できるわけではないが、それもまた御心だ。\n我々にできるのは、彼らの不滅の魂の安息を祈ることだけだ。";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "行こうぜ。俺たちの道はジャングルを抜けて、モスキート湾からそう遠くない洞窟へと続いているんだ。";
			link.l1 = "もちろんだ。そばにいて、絶対に離れるんじゃねえぞ。";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "ここに来たわね……昔、ラミロと私は若い頃にここで雨宿りしたのよ。彼が私の夫になる前のこと。その時、彼は 「どんなことがあってもお前の心を射止めてみせる」と言ってくれたの。";
			link.l1 = "旦那なしで一人でここまで来させてしまい、すまないな、セニョーラ。 こういう場所には多くの思い出が詰まっているんだ。少し見て回ろう――思い出だけじゃなく、ラミロが一番苦しい時のために残しておいたものも見つかるかもしれないぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"…何か見つけたのか？それはラミロが残したものか？空っぽなのが怖いのか、 それとも借金を返すには足りないのが怖いのか、自分でも分からないんだ…";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "（見せる）ほら、これが宝箱に入っていた全てだ。これであなたの運命が少しでも良くなるといいんだが。";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "俺はまだその箱の中を探しているところだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "ああ、船長！もちろんだ！これで十分だ！だが、あんたの助けに報酬なしってわけにはいかねえ。 百ドゥブロン受け取ってくれ。あんたがいなけりゃ、この隠し場所のことも知れなかったし、 いまだにラミロの借金取りが差し向けた連中から隠れてたはずだ……";
			link.l1 = "あなたはとても気前がいいですね、奥さん、ありがとうございます。\n俺たちの稼業じゃ、金は決して無駄にならねえんだ。";
			link.l1.go = "Marisa_34";
			link.l2 = "いいえ、奥さん。あなたの方がこの金をずっと必要としている。大事なのは、これであなたが悩みから解放されて、 平穏に暮らせることだ。それだけで俺には十分さ。";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Given: Amulet 'Cimaruta'", "None");
			notification("Given: Amulet 'Fisherman'", "None");
			notification("Given: Matchlock Musket", "None");
			notification("Given: Diamond (10)", "None");
			notification("Given: Ruby (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "「さて、」 "+GetSexPhrase("旦那",""+pchar.name+"")+"、そろそろ動き出そう。俺が町で見られてたら、誰かに尾けられてるかもしれねえ。ここに長居はしない方がいいぜ。";
			link.l1 = "マリサ、君の言う通りだ。行こう。";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "船長、どうかお願いします……夫はこの武器を家族を守るために持っていました。そして私は確信しています――あなたの手に渡れば、正義のために使われるはずです。ラミロも、 絶望の中で私を救ってくれたあなたのもとにこの武器が渡ったことをきっと喜ぶでしょう。";
			link.l1 = "わかった、マリサ、ありがとう。あなたは親切で誇り高い女性だ。本当に、 運命があなたにこれほど残酷だったことを悔やんでいるよ。";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "時には主が我々の信仰を試すために、困難な日々や年をお与えになることもある。しかし、 正しき道を歩む者を主は決して見捨てはしない。あなたを私の助けとして遣わしてくださったのだ、そして今、 私の最大の悩みも間もなく過ぎ去ることを願っている。\nだが今は、そろそろ戻る時だ。ここにはもう十分長く留まったし、 まだ私を探している者たちがいるから危険かもしれない。";
			link.l1 = "もちろん、旦那、行きましょう。";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "ははっ！ここにいたか、行方不明の奴め！まさか、こんなネズミ穴みてえな場所に隠れてりゃ、 俺に見つからねえとでも思ったのか？町中を何度もひっくり返して探したが、結局ここにいやがったんだな\n"+GetSexPhrase("それに加えて、ガキとデートまでしやがって。俺の金はどこだ、この小娘め？今すぐ渡さねえと、 この洞窟がてめえの墓場になるぞ。",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "お前……";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "つまり、女から借金を取り立てて食ってる奴ってわけか？その稼業を選んだ時点で、てめえに頭が回らねえのは明白だな。 自分でここまで来れたのが不思議なくらいだぜ。普通ならもっと賢い奴――例えば自分の靴でも――の後をついてくるのが関の山だろうよ。";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "黙れ、英雄さん。お前の番は後だ、まずはあの女と片付ける。あいつは五百二十五ドゥブロンの借金がある――利子込みだ。全額払わなきゃ、ここに永遠に残って虫の餌になるだけさ。だが、そんなに正義ぶるなら、 お前が肩代わりしてもいいぜ。そしたら俺は消える。";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "お前、自分がここにふらっと入ってきて、女を侮辱し、俺を無視して、 しかもドゥブロン金貨まで持って無傷で出ていけると思ってるのか？どうやら頭はあまり良くねえようだな。だが、 女の前で乱闘は始めねえ。だからこうしよう――カレデラ夫人に謝って、ドゥブロン金貨を持ってさっさと出ていけ。それが嫌なら、 俺が礼儀ってもんを叩き込んでやるぜ。";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "黙って順番を待て。この哀れな奴と片付けてからお前の相手をしてやる。こいつは五百二十五ドゥブロンの借金がある――利子込みだ。そんなに正義ぶるなら、お前がこいつの分を払えばいい。そしたら俺は引き上げるぜ。";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "まあ、俺はお前の荒っぽい態度も、俺に対する無礼も大目に見てやるさ。\nだがな、ドゥブロン金貨を手に入れて無事にここを出たいなら、カレデラ嬢に謝らなきゃならねえ。\nそうしないなら、どっちが武器の扱いが上手いか試してみることになるぜ。信じろよ、 俺は飾りで武器を持ち歩いてるわけじゃねえんだ。";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "どうやら、お前はあまり賢くねえらしいな。俺が順番を待つと思ったのか？それよりも、 お前やその仲間がカルデラ夫人にふりかかった厄介ごとを見て見ぬふりすると思ったなら、なおさらだぜ。";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "そうかい、好きにしな。余計な危険を冒さずに金を手に入れられるなら、俺が首を突っ込む理由はねえ。 ドゥブロンを渡せ――さっさと行け。";
			link.l1 = "まず、そのご婦人に謝れ。";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "許してください、旦那。悪魔に取り憑かれてしまいました。";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Happy"+GetSexPhrase("","")+"金貨を渡せば、俺はさっさと行くぜ。やることが山ほどあるんだ、お前と世間話してる暇なんかねえんだよ。";
			link.l1 = "ドブロンを持ってさっさと出ていけ。";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "船長、本当に、俺にはわからねえ……これはどういうことだ？";
			link.l1 = "これで借金はすべて帳消しだ。もう自由の身だぞ。";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "でも……今すぐ全額を返すことはできないんだ。\nもう少し待ってくれれば……";
			link.l1 = "マリサ、お前は分かってないぜ。俺には何も借りなんかねえし、もう誰にも借りなんかねえんだ。 見つけた金はきっとお前の役に立つさ。昔の生活に戻れ――教会が待ってるぞ。";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "俺…俺には信じられねえよ。こんなこと、起こるはずがねえんだ。 "+GetSexPhrase("旦那","お嬢さん")+"「！俺のために大金を払ったのに……それだけか？もう全部終わり？借金も追っ手もなし？教えてくれ、本当なのか？」";
			link.l1 = "本当ですよ、奥さん。すべて終わりました。もう誰にも借りはありません。";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "ああ、船長、あなたはなんて高貴なお方なのでしょう！まるで神様が遣わしたように感じます！でも、 どう感謝すればいいのか想像もつきません。あなたは……私の人生をすっかり変えてくれました、そして私は……いったい何をお返しできるのでしょうか？";
			link.l1 = "何もする必要はない、マリサ。生きていればいいんだ。恐れずに、過去の鎖に縛られずにな。昔の生活に戻って、 その中で幸せを見つけてくれ――それが俺への一番の恩返しになるさ。さあ、町まで送っていこう。";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "「何をしたんだ、船長、あんたがあいつを殺したじゃねえか！」";
			link.l1 = "そうだよ、奥さん。あんたとあんたの名誉を守らなきゃならなかったんだ……";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "ああ、船長、たとえあの男のような者でも命を奪うことは恐ろしい重罪です！ その罪を少しでも不滅の魂から洗い流すには、昼も夜も祈り続けねばなりません。神に誓って言いますが、 私は持っている物すべてを彼に渡せば、彼は立ち去ったでしょう……しかし今は……今や彼の血はあなたの手にあり、許されるかどうかは天のみぞ知るのです！";
			link.l1 = "もしかすると、それは主のお導きだったのかもしれません。しかし、そのことはもう考えないでおきましょう。\nそれより、この洞窟から出ましょう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "船長、改めてお礼を申し上げます！あなたのご健康とご多幸をお祈りいたします。 "+pchar.name+"。どうか、私たちの教会へお越しください――主があなたのすべての罪をお赦しになり、祝福を授けてくださいますように。";
			link.l1 = "そのうち寄ってみるかもな。\nそれと覚えておけよ、マリサ。もしお前の嬉しそうな顔がそこになかったら、俺はがっかりしちまうぜ。";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "「ああ、」 "+GetAddress_Form(NPChar)+"…あなたは本当に親切ですね。また私たちの町でお会いできるのを心から楽しみにしています。\nでも今は、どうかお許しください。早く自分の生活を立て直して、 この良い知らせをドロレスに伝えたくてたまらないのです。";
			link.l1 = "もちろんだ、マリサ。さようなら。体に気をつけてな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "船長、改めて私の尽きぬ感謝をお伝えさせてください！あなたは私にとって不可能を成し遂げてくれました！ そのご親切と高潔さに報いるため、過去二年間、私がどのようにして傭兵たちを避けてきたのかをお話ししたいのです。\nこの知識が、いつかあなたのお役に立つかもしれません。";
			link.l1 = "ありがとうございます、奥さん。こういう時は知識が金と同じくらい価値があるんだ。話を聞こう。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "これが俺のこの二年間の過ごし方だ。\n力が全てのこの世界で、影に潜む術を知っていれば、他の連中が夢見るだけの機会が手に入るんだぜ。";
			link.l1 = "話を聞かせてくれてありがとう、マリサ。いろいろな苦労をしてきたんだな、その経験は本当に貴重だよ。";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "また我々の町でお会いできれば本当に嬉しく思います。\nどうか教会へお越しください――主があなたのすべての罪をお許しになり、祝福を授けてくださいますように。";
			link.l1 = "そのうち立ち寄るかもしれねえ。\nそれと覚えておけよ、マリサ、もしお前の楽しそうな顔がそこになかったら、俺はがっかりするぜ。";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "ああ、船長……あなたは本当に親切ですね。ですが、今はお許しください、早く自分の人生を立て直して、 この良い知らせをドロレスに伝えたくてたまらないのです。";
			link.l1 = "もちろんだ、Marisa。さようなら。体に気をつけてな。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Did you hear? Captain "+GetFullName(pchar)+" paid off Calder's widow’s debt from his own pocket! Not many would part with that kind of money for a stranger. Seems Spain still has true caballeros left!","It warms the heart to see that Spain is home not only to worthy caballeros, but also to women whose honor and courage rival any man’s.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("They say a certain captain paid his own money to free Calder’s widow from her late husband’s debts! Not everyone would act so nobly. A true person of honor, don’t you think?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "船長、またお会いできて本当に嬉しいです！お立ち寄りいただけるのを楽しみにしておりました。\n今日は少しお時間があって、ご一緒にお祈りしていかれませんか？";
						link.l1 = "Glad"+GetSexPhrase("","")+" 会えて嬉しいよ、マリサ。だが、今はゆっくりしている余裕はないんだ。主への務めは覚えているが、 祈りは後回しにしなきゃならない。";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "船長、またお会いしましたな！いつも歓迎しますぞ。主はあなたに教会への道を忘れさせてはくれんようですな……結局、祈りの時間を取れるかもしれませんな？";
						link.l1 = "マリサ、会えて嬉しいよ。\nだが、ここには長くいられない――俺の用事は待ってくれないんだ。\n祈らずとも、主は俺の思いを知っておられると信じている。";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "船長、またお会いできてなんと嬉しいことでしょう！毎日、あなたのご親切に感謝して主に祈っております。 あなたが助けてくださったおかげで、世界が明るくなりました。";
						link.l1 = "Glad"+GetSexPhrase("","")+"   元気そうで何よりだ、マリサ。これ以上嫌な出来事に遭っていないといいが。前よりずっと幸せそうに見えるぞ。";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "船長、お会いできて本当に嬉しいです！\nあなたが教会に来てくださるたび、私は心が安らぎます。\nあなたは善き行いの光をもたらしてくださいます。";
						link.l1 = "そして俺も嬉しいぜ"+GetSexPhrase("","")+" 会えて嬉しいよ、マリサ。静かな暮らしにはもう慣れたか？それとも時々昔を振り返ったりするのか？";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+"、もし皆が祈りを後回しにしていたら、とっくに世界は闇に落ちていただろう。しばらく悩みを脇に置きなさい――悔い改めは前に進む力を与えてくれるのだ。";
			link.l1 = "わかっているよ、マリサ。でも今は本当に無理なんだ。言葉がなくても主はきっと私の声を聞いてくださると信じている。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+"、考え直しましたか？罪は勝手に消えるものではありませんし、待てば待つほど重くなるのです。";
			link.l1 = "残念だが、もう行かねばならん。だが次こそ、必ず祈ると約束するぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "しかし、信仰とは知ることだけでなく、行動することでもあるのです！救済への道をいつまでも先延ばしにはできません。 罪の重荷を捨て去って安堵を感じたくはありませんか？";
			link.l1 = "たぶん、だが今じゃない。祈りが後回しになっても、主よ、どうか私の声をお聞きください。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "船長、悔い改めを先延ばしにするのは、それ自体が罪だと思いませんか？\nいつか手遅れになるかもしれませんよ。";
			link.l1 = "たぶんそうかもしれませんが、今日は時間がありません。\n信仰は私と共にあり、祈らずとも主は私の悔い改めを見ておられます。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "はい、おかげさまでまた自由に息ができます。主があなたとあなたの旅路を見守ってくださいますように。よろしければ、 一緒にお祈りしませんか？";
			link.l1 = "あなたの祈りは今のままで十分強いと私は信じています。\n最も大切なのは、今あなたの周りに優しさしかないということです。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+"、やっぱり気が変わったのか？我らの創造主に祈ろうか？";
			link.l1 = "残念だが、マリサ、俺はもう行かなくちゃならねえ、やることがあるんだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "俺は前だけを見るようにしてるんだ。今は未来がある、それも全部あんたのおかげだぜ。\nこのことは一緒に神様に感謝すべきかもしれねえな？";
			link.l1 = "お前なら俺よりもうまくやれると思うぜ。大事なのは、お前の祈りが安らぎをもたらすことだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+"「……せめて一つだけでも祈りを捧げていただけませんか？」";
			link.l1 = "許してくれ、マリサ、だが残念ながら今は時間がないんだ。俺のためにも祈ってくれ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "船長、ここじゃありません。俺たちが探してる洞窟はモスキート湾のそばにあります。";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}