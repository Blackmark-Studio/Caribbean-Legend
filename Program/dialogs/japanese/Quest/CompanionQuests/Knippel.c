void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
			link.l1 = "「何でもねえ。」";
			link.l1.go = "exit";
		break;
		
		// Квест "Длинные тени старых грехов"
		case "DTSG_Knippel_1":
			dialog.text = "ああ、今日はなんて暑いんだ。こんなむし暑さから逃れるためなら、 足にチェーンショットをくくりつけて海に飛び込んだっていいくらいだぜ！";
			link.l1 = "ははっ、チャーリー！…お前さん、それはちと過激すぎるんじゃねえか。でも、喉を潤すのは悪くねえな――今日は本当に暑すぎるしな。どうだ、付き合うか？";
			link.l1.go = "DTSG_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Knippel_2":
			dialog.text = "一杯やるのか、船長？いつでも大歓迎だぜ！";
			link.l1 = "そうこなくちゃな。行くぜ！";
			link.l1.go = "DTSG_Knippel_3";
		break;
		
		case "DTSG_Knippel_3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_1");
		break;
		
		case "DTSG_Ohotnik_1":
			dialog.text = "おい、水夫、あんたは何でも見てきた顔してるな！一杯やって、武勇伝でも語り合おうぜ？奢るからよ！";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_1_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
			
		break;
		
		case "DTSG_Ohotnik_1_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_2":
			dialog.text = "ああ、いや、遠慮しとくぜ、相棒。俺は自分の船長と一緒にここへ来たんだ。他を当たってくれ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_2_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
			locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;
		
		case "DTSG_Ohotnik_2_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
			locCameraSleep(true);
		break;
		
		case "DTSG_Ohotnik_3":
			dialog.text = "はっ、こんなボロ野郎が偉そうに、船長としか飲まねえってのか？";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_3_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_3_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_4":
			dialog.text = "高く評価されてるだと？！俺は何十年も王立海軍で務めてきたんだぜ！しかも貴族どものためじゃねえ、 俺やお前みたいな普通の連中のために戦ってきたんだ、どこでも法と秩序を守るためにな！..";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_4_Animation";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_4_Animation":
			StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_5":
			dialog.text = "大口叩きやがって、飲む相手は船長や貴族ばかりじゃねえか！やっぱり海軍じゃ、 大砲の磨き方しかちゃんと教わらなかったんだな、ははっ！";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_5_Animation";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;
		
		case "DTSG_Ohotnik_5_Animation":
			StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_Ohotnik_6":
			dialog.text = "鎖弾を喉にぶち込んでやるぞ、小僧！";
			link.l1 = "「チャーリー、そんなに取り乱すなよ、そこまでのことじゃねえだろ。」";
			link.l1.go = "DTSG_Ohotnik_7";
			LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		
		case "DTSG_Ohotnik_7":
			dialog.text = "ここは俺に任せてくれ、船長。海軍の名誉がかかってるんだ、俺自身で守らなきゃならねえ、 誰かの陰に隠れるわけにはいかねえんだ…";
			link.l1 = "...";
			link.l1.go = "DTSG_Ohotnik_8";
		break;
		
		case "DTSG_Ohotnik_8":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_1");
		break;
		
		case "DTSG_Knippel_l0":
			dialog.text = "待たせてすまねえな、船長。あんまり時間はかからなかったと思うが。";
			link.l1 = "気にするな。怪我はないか？あの野郎、なかなかやるじゃねえか。";
			link.l1.go = "DTSG_Knippel_l1";
		break;
		
		case "DTSG_Knippel_l1":
			dialog.text = "気にするな、船長。大事なのは、あいつが報いを受けたってことだ。奴の死体から何か鍵みたいなものを拾ったんだ…";
			link.l1 = "...";
			link.l1.go = "DTSG_Knippel_l2";
		break;
		
		case "DTSG_Knippel_l2":
			dialog.text = "あいつの死体から何かの鍵を拾ったんだが……何に使うものなんだろうな？";
			link.l1 = "簡単なことだぜ、チャーリー……扉とか宝箱ならな、はは。こいつについては宿屋の主人に話を聞いてみようぜ、役に立つかもしれねえ。";
			link.l1.go = "DTSG_Knippel_l3";
			AddItems(pchar, "Key1", 1);
			Log_info("Charlie gave you the key.");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_Knippel_l3":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2");
		break;
		
		case "DTSG_Knippel_20":
			dialog.text = "信じられねえ……";
			link.l1 = "「チャーリー、お前も俺と同じことを考えてるのか？」";
			link.l1.go = "DTSG_Knippel_21";
		break;
		
		case "DTSG_Knippel_21":
			dialog.text = "俺はどうだか知らねえが、旦那、ここにこんな大金があるとは驚いたぜ。あいつ、商人でも貴族でもなく、 ただの普通の男に見えたのにな。";
			link.l1 = "大したことじゃねえが、確かにその通りだ。だが驚いたのは、この妙に焦げた手紙だぜ。";
			link.l1.go = "DTSG_Knippel_22";
		break;
		
		case "DTSG_Knippel_22":
			dialog.text = "ああ、あいつも間抜けだったな――頑丈な船体にチェーンショットを撃ち込むようなもんだぜ。手紙なんざ、跡形もなく燃やしちまえばよかったんだ。";
			link.l1 = "確かにそうだ。だが、それじゃ俺たちの助けにはならねえ――あいつが誰だったのか、誰とやり取りしてたのかも分からねえしな。\n行くぞ、チャーリー。ここにはもう用はねえ。";
			link.l1.go = "DTSG_Knippel_23";
		break;
		
		case "DTSG_Knippel_23":			//КОНЕЦ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_2_1");
		break;
		
		case "DTSG_Ohotnik_10":
			dialog.text = "お前が自慢してたあのロイヤル・ネイビーもこのざまだな、ぷっ！";
			link.l1 = "チャーリーは善良でまともな男だった。しかも、彼は砲術士であって、海兵じゃなかったんだ。";
			link.l1.go = "DTSG_Ohotnik_11";
		break;
		
		case "DTSG_Ohotnik_11":
			dialog.text = "砲手だと？！だから俺の言った通りじゃねえか、ははは！それに、そんなに睨むなよ――誰を仲間にしたか、最初から分かってたはずだろ。";
			link.l1 = "誰に手を出してるのか、分かってたはずだろう。";
			link.l1.go = "DTSG_Ohotnik_Agressia_1";
			link.l2 = "「お前がまだ生きてるのは正々堂々と勝ったからだ。だからその腐った口を閉じて、とっととここから出ていけ。」";
			link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;
		
		case "DTSG_Ohotnik_Otpustil_1":
			dialog.text = "さて、次はお前と戦うことになるかと思ってたぜ。\n名誉を大事にしてるって聞けて嬉しいもんだ。";
			link.l1 = "チャーリーにとっても、ただの口先だけじゃなかったんだ。\nだが、お前のこととなると、俺は疑ってるぜ。\nまあ、今となっちゃどうでもいいことだがな。";
			link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;
		
		case "DTSG_Ohotnik_Otpustil_2":			//ПРОВАЛ ЭТАПА 1
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_2");
		break;
		
		case "DTSG_Ohotnik_Agressia_1":
			dialog.text = "俺が相手にしたのは、甘やかされたひ弱野郎か！？自分のその薄っぺらい口ひげ、見たことあるのかよ…";
			link.l1 = "お前は本当に人を苛立たせるのが上手いな……その分、お前に俺の怒りをぶつけるのが余計に気持ちいいぜ。";
			link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;
		
		case "DTSG_Ohotnik_Agressia_2":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Ohotnik_DlgExit_3");
		break;
		
		case "DTSG_PiterAdams_1":
			dialog.text = "待ってくれ、船長。あんたが立派で高潔な人間だってのはわかる、ちょっと頼みがあるんだ。\n名誉に関わることなんだ。";
			link.l1 = "できるかもしれねえが、どうしたんだ？それに、なんで俺のところに来たんだ？ この辺りには立派な連中がたくさんいるだろうに。ところで、俺は誰と話してるんだ？\n";
			link.l1.go = "DTSG_PiterAdams_2";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "DTSG_PiterAdams_2":
			dialog.text = "ピーター。ピーター・アダムズ。お前はよくいる甘やかされた名家の坊ちゃんじゃなくて、 頼りになる腕の立つ男だとわかるぜ。";
			link.l1 = "おお、俺がカリブに初めて来た時を見てほしかったぜ、旦那。で、どうした？何か手伝いがいるのか？";
			link.l1.go = "DTSG_PiterAdams_3";
		break;
		
		case "DTSG_PiterAdams_3":
			dialog.text = "俺の代わりに……決闘してくれねえか、旦那？地元の厄介者、ラルフ・ファグルが俺の女房を侮辱しやがったんだ。しかも公衆の面前で、 しつこく絡みやがってよ。俺の目の前でだぜ。信じられるか？\n";
			link.l1 = "決闘を申し込んでおいて、他人の陰に隠れるなんて、名誉も何もあったもんじゃねえよ。\nしかも、かかってるのは自分だけの名誉じゃなくて、女の、それも自分の妻の名誉だろうが。\nそう思わねえか、アダムズ？なんで自分の女のために自分で戦えねえんだ？";
			link.l1.go = "DTSG_PiterAdams_4";
		break;
		
		case "DTSG_PiterAdams_4":
			dialog.text = "あんたの言う通りだ、まったくその通りだよ。ただ、最近ひどい熱にやられてな、やっとのことで立ってるくらいなんだ\n正直、こんな頼みごとをするのは俺にとっちゃ簡単じゃねえ。もし自分が侮辱されたんなら我慢したさ。でも、 女房の名誉がかかってるとなりゃ話は別だ！俺は臆病者じゃねえ、旦那。かつては王立海軍に仕えて、 あのロバート・ブレイクと同じ船で航海したこともあるんだぜ！";
			link.l1 = "俺は…";
			link.l1.go = "DTSG_PiterAdams_5";
		break;
		
		case "DTSG_PiterAdams_5":
			StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_6":
			dialog.text = "俺たちが手を貸すぜ。";
			link.l1 = "「チャーリーか…？」";
			link.l1.go = "DTSG_PiterAdams_7";
			CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams"))
		break;
		
		case "DTSG_PiterAdams_7":
			dialog.text = "あいつは立派な男だぜ、船長。それが本当じゃなきゃ、この俺、砲弾に打たれて地獄行きでもかまわねえ！ ブレイク提督と共に仕えた連中はみんな偉大だった。奴らは力を合わせて、誰にも庶民を虐げさせなかったんだ\nそしてあの人のおかげで、ジャマイカはスペイン野郎どもの圧政から解放されたんだ！";
			link.l1 = "たとえそうだとしても、俺の部下が俺の話を遮ったり、勝手に決めたりするのは許さねえ。わかったか？";
			link.l1.go = "DTSG_PiterAdams_8";
			link.l2 = "わかってる、本当にさ。だが、まだ俺は返事すらしてねえんだ。今後はそんなにせっかちになって、 俺の話を遮るのはやめてくれよ、いいな？";
			link.l2.go = "DTSG_PiterAdams_8";
			CharacterTurnByChr(npchar, pchar)
		break;
		
		case "DTSG_PiterAdams_8":
			dialog.text = "言っとくぜ、船長。あんたがこの男を助けねえなら、年寄りのチャーリーが全部投げ出してでも、 俺がこの男のために一人で決闘してやるさ。ここで地獄に落ちてもかまわねえ！";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "静かにしろ、俺は手伝わねえなんて言ってねえぞ。そうだろ、アダムズ旦那？";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
			}
			else
			{
				link.l1 = "正直言って、チャーリー、お前のせいで俺が臆病者みたいに見えるじゃねえか。 俺は今まで一度もそんな奴じゃなかったんだぜ。それくらい分かってるだろ。";
				link.l1.go = "DTSG_PiterAdams_NN_1";
			}
		break;
		
		case "DTSG_PiterAdams_NN_1":
			dialog.text = "あっ、すまねえ、船長、つい熱くなっちまった。";
			link.l1 = "大丈夫だ。だが、自分を抑えておけよ、いいな？";
			link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;
		
		case "DTSG_PiterAdams_NN_1_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_NN_2":
			dialog.text = "";
			link.l1 = "あんたのために決闘してやるぜ、アダムズ旦那。";
			link.l1.go = "DTSG_PiterAdams_NN_3";
		break;
		
		case "DTSG_PiterAdams_NN_3":
			dialog.text = "ありがとうございます、旦那！神のご加護を！";
			link.l1 = "「ロード・プロテクターにもご加護を、そうだろう、アダムズさん？心配すんな、 チャールズ・ド・モールは正直者を困ったままにはしねえぜ。」";
			link.l1.go = "DTSG_PiterAdams_NN_4";
		break;
		
		case "DTSG_PiterAdams_NN_4":
			dialog.text = "感謝するぜ、ド・モール旦那、旦那！ジェーンと俺と一緒に夕飯でもどうだ？";
			link.l1 = "ええと、俺は……";
			link.l1.go = "DTSG_PiterAdams_NN_5";
		break;
		
		case "DTSG_PiterAdams_NN_5":
			dialog.text = "俺は譲らねえぞ！";
			link.l1 = "まあ、どうしてもって言うならな。ありがとう、ピーター。案内してくれ。";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_1":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_PiterAdams_Nastoroje_2":
			dialog.text = "もちろん本当だぜ、旦那！ジェーンと一緒にこっちに来て、旅の疲れを休めちゃどうだ？";
			link.l1 = "ありがとうよ、だが、お前の好意につけ込むのは本当に正しいことなのか？";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_3":
			dialog.text = "いや、逆に来てくれなかったら、俺たちは気を悪くするぜ、船長。";
			link.l1 = "その時はどうして断れたんだ？先に行け、ピーター！";
			link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;
		
		case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_3");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_1":
			dialog.text = "俺たちだ！どうぞ、中へ入ってくれ。";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
			{
				link.l1 = "ありがとう。ジェーンと話してもいいか？どうしてそんなことになったのか、詳しく聞いてくれ――全部の事情が知りたいんだ。";
				link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
			}
			link.l2 = "申し訳ねえが、考え直した結果、断らせてもらうぜ。これから決闘の準備をしなきゃならねえんだ。\nところで、その決闘はどこで、いつ行われるんだ？";
			link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_2":
			dialog.text = "もちろんだ、旦那。俺たちは喜んで話すし、どんな質問にも答えるぜ。ついてきてくれ。";
			link.l1 = "ありがとう、Peter。";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_3":
			DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_4":
			dialog.text = "なんてこった！だが、確かにその通りだ、しっかり準備しないとな。二時間後だ。\n街の門のすぐ外で待ってるぜ。";
			link.l1 = "了解だ、ありがとう。終わったら喜んで行くぜ。じゃあ、その時に会おう！";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;
		
		case "DTSG_PiterAdamsRyadomSDomom_5":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_4");
		break;
		
		case "DTSG_JeinAdams_1":
			dialog.text = "いらっしゃい！旦那、客を連れてくるなんて聞いてなかったぞ――ちゃんと準備しておけばよかったのう。";
			link.l1 = "ありがとうございます、奥さん、長居はしません。シャルル・ド・モール、あなたのお役に立ちます。 ご主人と一緒にお話を伺うと約束しました。どうしてこうなったのか教えてください。";
			link.l1.go = "DTSG_JeinAdams_2";
		break;
		
		case "DTSG_JeinAdams_2":
			dialog.text = "ああ、ひどかったんだ！ラルフは完全に酔っぱらっててな。ご近所の連中の前でも、ピーターの前ですら、 俺にいやらしいことを言いながら絡んできやがったんだ…";
			link.l1 = "「そいつはお前に何て言ったんだ？」";
			link.l1.go = "DTSG_JeinAdams_3";
		break;
		
		case "DTSG_JeinAdams_3":
			dialog.text = "恥ずかしくて話せねえよ。それからあいつは酔いがさめて、そして…";
			link.l1 = "謝って決闘を取り消してくれと頼んだ、とでも言うのか？";
			link.l1.go = "DTSG_JeinAdams_4";
		break;
		
		case "DTSG_JeinAdams_4":
			dialog.text = "一度もない。";
			link.l1 = "お気の毒に思います。もしよろしければ、もう一つお聞きしたいことがございます、奥様。";
			link.l1.go = "DTSG_JeinAdams_5";
		break;
		
		case "DTSG_JeinAdams_5":
			dialog.text = "「それは何だ、旦那？」";
			link.l1 = "どんな人生の事情や試練があって、あんたと旦那さんはここで暮らすことになったんだ？旦那さんの功績を考えれば、 イギリスのどの都市でも、ラルフなんぞとっくに黙らせていただろうに。";
			link.l1.go = "DTSG_JeinAdams_6";
		break;
		
		case "DTSG_JeinAdams_6":
			StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_7":
			dialog.text = "失礼しますが、旦那、よくもそんなことを言えたもんだな！？あんたが俺の船長じゃなきゃ、 チェーンショットでもぶん回して一発お見舞いしてやるところだぜ！\nアダムズさんみたいな立派な男を疑うだけじゃなく、困ってるご婦人まで馬鹿にするなんて…";
			link.l1 = "俺が女をからかったのを聞いたか？いや？なら、俺を中傷するな。俺たちの仲間なら助けられたかもしれねえから、 そう聞いたんだ。";
			link.l1.go = "DTSG_JeinAdams_8a";
			link.l1 = "落ち着け、チャーリー！どうしてそんな……俺はただ、ジェーンとピーターがどんな苦労をしたのかもっと知って、同情したかっただけだ。イギリスの植民地なら、 今ごろきっと助けられていただろうに。";
			link.l1.go = "DTSG_JeinAdams_8b";
		break;
		
		case "DTSG_JeinAdams_8a":
			dialog.text = "人生なんてどう転ぶかわからねえ……難破もあれば、誰かの中傷で、時にはこんな誠実な人間ですら恥を忍んで身を隠さなきゃならなくなることもあるんだ\nそんなに疑り深くて用心深いってんなら、近所の連中にでも聞いてみな。 きっと俺の言うことを全部裏付けてくれるはずだ。でもな、 年寄りチャーリーは人の不幸を陰で噂するような真似はしねえぜ！";
			link.l1 = "俺の言うことが聞こえなかったのか？俺はこの人たちを助けるって言ったんだぜ。";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;
		
		case "DTSG_JeinAdams_8b":
			dialog.text = "人生ってのはどう転ぶかわからねえもんだ……難破だってあるし、誰かの中傷で、時にはこんな誠実な人間ですら恥を忍んで身を隠さなきゃならねえこともあるんだ\nそんなに疑り深くて用心深いってんなら、近所の連中にでも聞いてみな。きっと全部本当だって証言してくれるさ。 でもな、年寄りのチャーリーは、他人の不幸を陰でこそこそ話すような真似はしねえぜ！";
			link.l1 = "俺の言ったことが聞こえなかったのか？俺はこの連中を助けるって言ったんだ。";
			link.l1.go = "DTSG_JeinAdams_9";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;
		
		case "DTSG_JeinAdams_9":
			StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_JeinAdams_10":
			dialog.text = "心の底から感謝するぜ。俺たちは祈りの中であんたのことを忘れねえよ。";
			link.l1 = "それはいい。ところで、俺たちの件だが。アダムズ旦那、決闘の場所と時間はどこで決めたんだ？";
			link.l1.go = "DTSG_JeinAdams_11";
		break;
		
		case "DTSG_JeinAdams_11":
			dialog.text = "街門の外だ、旦那。二時間後だ。";
			link.l1 = "俺はやり遂げるぜ。いい知らせを持って戻るからな。俺の冥福を祈ってロウソクを灯すなんて、まだ早いぞ！";
			link.l1.go = "DTSG_JeinAdams_13";
		break;
		
		case "DTSG_JeinAdams_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;
		
		case "DTSG_Knippel_30":
			dialog.text = "何か気になることでもあるのかい、船長？ずいぶん考え込んでるように見えるぜ。";
			link.l1 = "そうだな、ああ。アダムズの話、どうも辻褄が合わねえし……";
			link.l1.go = "DTSG_Knippel_31";
		break;
		
		case "DTSG_Knippel_31":
			dialog.text = "「いつまでこんなことが続くんだ、旦那！？誰かが助けを必要とするたびに、毎回こんなふうに反応するのか？」";
			link.l1 = "頼むから、静かに話してくれ。通り中に聞こえるような大声を出すな。決闘に行くと言っただろう。 それで十分じゃねえのか？今から俺の話をよく聞け。";
			link.l1.go = "DTSG_Knippel_32";
		break;
		
		case "DTSG_Knippel_32":
			dialog.text = "ふむ、わかったぜ、船長。さっきはつい熱くなっちまって悪かったな――王立海軍で働いてた連中の運命が気になって仕方ねえんだ。俺たちの多くはまともな奴らで、 本当はもっとましな人生を送るべきだったんだよ。";
			link.l1 = "分かったぞ、チャーリー。さて、やるべきことを覚えておけ。乗組員の何人かを街門まで送ってほしい。\n決闘の時が近づいたら、やつらに静かに集まらせて、俺の合図を待つようにしてくれ。";
			link.l1.go = "DTSG_Knippel_33";
		break;
		
		case "DTSG_Knippel_33":
			dialog.text = "「正々堂々の決闘を殺しに変えるつもりか？」";
			link.l1 = "全部が正直だとは思えねえな。必要な時だけ合図するぜ。もし本当に潔白なら、俺の間違いでも構わねえさ。\n今ならわかるか？一ヶ月前に何があったか覚えてるか？";
			link.l1.go = "DTSG_Knippel_34";
		break;
		
		case "DTSG_Knippel_34":
			dialog.text = "了解だ、旦那。正直言って、あまり気が進まねえが、必要なことはやるさ。心配すんな。";
			link.l1 = "それが聞きたかったんだ。";
			link.l1.go = "DTSG_Knippel_35";
		break;
		
		case "DTSG_Knippel_35":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_DlgExit_5");
		break;
		
		case "DTSG_RalfFaggl":
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			PChar.quest.DTSG_PoP_DuelTime.over = "yes";
			PChar.quest.DTSG_PoP_Duel.over = "yes";
			dialog.text = "そうか、ド・モール。お前、早く来たな。しかもまだ街の中だ。\nまあ、関係ねえがな。あの年寄りの間抜けを連れてこなかったのは残念だが、心配すんな、 いずれあいつにも手を出してやるさ。";
			link.l1 = "いつでもお役に立つぜ。傭兵か？俺が誰の邪魔をしたってんだ？";
			link.l1.go = "DTSG_RalfFaggl_2";
		break;
		
		case "DTSG_RalfFaggl_2":
			dialog.text = "そういうことだ、誰もいねえ。俺たちが狙ってるのはあのジジイ、チャーリーだ。お前を通して探す方が楽なんだよ、 今はお前の船にいるって聞いたからな。ここはジャングルじゃねえ、だから騒ぎになる前に素早く動かねえとな。 だがここなら、少なくともお前は逃げられねえぞ。";
			link.l1 = "この決闘騒ぎ自体が罠だったんじゃねえか？";
			link.l1.go = "DTSG_RalfFaggl_3";
		break;
		
		case "DTSG_RalfFaggl_3":
			dialog.text = "それに気づくのがちょっと遅いぜ、友よ。どうせ戦うことになってただろう――俺はラルフ・ファグル、よろしく頼む。";
			link.l1 = "実は、なんとなくそうじゃないかと思って、近所の連中に話を聞いてみたんだ。\nところで、アダムズもこの件に関わってるのか？それとジェーンは？まさか、あいつも……";
			link.l1.go = "DTSG_RalfFaggl_4";
		break;
		
		case "DTSG_RalfFaggl_4":
			dialog.text = "好奇心は猫を殺すって聞いたことねえのか？決闘に来いと命じられただけで、余計な詮索はするなってことだ。 この騒ぎを生き延びるチャンスがあったかもしれねえのによ\nもちろんだ。年寄りの軍人を挑発して、その上官に決闘を強いる――まさに俺たちがピーターと考えた完璧な作戦だぜ。ジェーンも自分の役目をしっかり果たしたしな。";
			link.l1 = "教えてくれ、誰がチャーリーを消そうとしたんだ？";
			link.l1.go = "DTSG_RalfFaggl_5";
		break;
		
		case "DTSG_RalfFaggl_5":
			dialog.text = "はっ、俺が教えるとでも思ったか？かかってこい。";
			link.l1 = "残念だな。じゃあ後でピーターに聞くとするか。";
			link.l1.go = "DTSG_RalfFaggl_6";
		break;
		
		case "DTSG_RalfFaggl_6":
			DialogExit();
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl");
			LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_PiterAdams_11":
			dialog.text = "おお、俺の話をちゃんと心に留めて、ラルフをもう罰したんだな、船長。";
			link.l1 = "もちろんだ、言った通り、俺は立派で高潔な男だからな。さて、この裏切りの罠の報いとして、 お前を罰することになるぜ。";
			link.l1.go = "DTSG_PiterAdams_12";
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			GiveItem2Character(npchar, "letter_1");
			ChangeItemName("letter_1", "itmname_specialletter");
			ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;
		
		case "DTSG_PiterAdams_12":
			dialog.text = "やってみるがいいさ、船長――どうせもう疲れ果てて傷だらけじゃねえか。";
			link.l1 = "じゃあ、ひと休みしようぜ。\nその間に教えてくれ、お前は誰の下で働いてるんだ？";
			link.l1.go = "DTSG_PiterAdams_13";
		break;
		
		case "DTSG_PiterAdams_13":
			dialog.text = "悪いが、俺の後ろ盾はそれを許しちゃくれねえんだ。たとえこの後でお前を片付けたとしてもな。ちなみに、 それが今まさに起きるってわけだ。";
			link.l1 = "くそっ…";
			link.l1.go = "DTSG_PiterAdams_14";
		break;
		
		case "DTSG_PiterAdams_14":
			DialogExit();
			
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, GetCharacterBaseHPValue(sld)/2, GetCharacterBaseHPValue(sld));
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			else
			{
				sld = CharacterFromID("DTSG_FrederikStouks");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
				LAi_KillCharacter(sld);
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "DTSG_Knippel_40":
			dialog.text = "信じられねえ…あいつら、俺たちを騙しただけじゃなく、王立海軍についてまで嘘をつきやがった！なんて奴らだ！もし生きてたら、 こんな裏切りにはチェーンショットを二発くらい飲ませてやるところだぜ！..";
			link.l1 = "人は色んなことで嘘をつくもんだ、チャーリー。お前ならよく知ってると思ってたぜ。だが、お前が確実に知ってるのは、 奴らを送り込んだやつが誰かってことだ。最近、お前に仕掛けられた罠はこれが初めてじゃねえ。 奴らはお前の特徴を細かく書いた手紙まで持ってた。いったい誰をそこまで怒らせたんだ？";
			link.l1.go = "DTSG_Knippel_41";
		break;
		
		case "DTSG_Knippel_41":
			dialog.text = "ああ、俺は……アダムズの家でもう何か見つかるかもしれねえな、旦那？";
			link.l1 = "話をはぐらかしてるのか？まあ、確かに、どうせ徹底的に調べるつもりだったんだ。行くぞ。";
			link.l1.go = "DTSG_Knippel_42";
		break;
		
		case "DTSG_Knippel_42":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
			PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;
		
		case "DTSG_Knippel_50":
			dialog.text = "なんてこった、こんなに大量の金貨があるとはな！";
			link.l1 = "ここには他に何もねえのが残念だな。『ジェーン』もどこにも見当たらねえ。あいつ、まだ生きてると思うか？";
			link.l1.go = "DTSG_Knippel_51";
		break;
		
		case "DTSG_Knippel_51":
			dialog.text = "わからねえな、旦那、ああいうろくでなしどもは何だってやりかねねえ……";
			link.l1 = "確かにそうだが、俺にはお前が言ってる以上のことを知ってるように思えるぜ。\nあいつらに狙われるのは今回が初めてじゃねえし、毎回あいつらの死体から大金が出てくるんだ。";
			link.l1.go = "DTSG_Knippel_52";
		break;
		
		case "DTSG_Knippel_52":
			dialog.text = "わからねえな、船長。でもたぶん、セント・ジョンズの金貸しかもしれねえ。";
			link.l1 = "「どうやってあいつを裏切ったんだ？」";
			link.l1.go = "DTSG_Knippel_53";
		break;
		
		case "DTSG_Knippel_53":
			dialog.text = "そうだな……少し前に、他の借金を全部返すためにあいつから金を借りたんだ。リチャードが払ってくれるって約束してくれたんだが……";
			link.l1 = "あいつがやらなかったとでも思うのか？";
			link.l1.go = "DTSG_Knippel_54";
		break;
		
		case "DTSG_Knippel_54":
			dialog.text = "前は信じられなかったが、あいつがあんたにしたことと、アビと一緒に慌ててカリブを去った後じゃ……借りを忘れちまったのかもしれねえ。いや、忘れてなくても結局出て行ったのか……リチャードの奴、本当にクソ野郎だったぜ、旦那。もしまたそれが本当だったとしても驚きはしねえが、 やっぱりがっかりするな。";
			link.l1 = "早まって決めつけるなよ、チャーリー。\nじゃあ、セントジョンズに行くぞ。";
			link.l1.go = "DTSG_Knippel_55";
		break;
		
		case "DTSG_Knippel_55":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			TakeItemFromCharacter(pchar, "letter_1");
			AddQuestRecord("DTSG", "5");
			QuestOpenSeaExit()
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_PiterAdams_20":
			if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
			{
				dialog.text = "おお、旦那、ここにいたか――どうやら皆、早めに集まることにしたようだな。\nその様子を見るに、ずいぶんと気楽そうじゃねえか。自分の腕にそんな自信があるのか？";
				link.l1 = "もちろん、これが俺の初めての決闘ってわけじゃねえ。";
				link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
				ChangeCharacterComplexReputation(pchar, "authority", 1);
			}
			else
			{
				dialog.text = "来てくれないんじゃないかと心配してたんだ、旦那。ほかの連中はもう来てるぜ。";
				link.l1 = "本物の紳士が遅れるのは、自分の死だけだ。";
				link.l1.go = "DTSG_PiterAdams_NN_21";
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
			}
		break;
		
		case "DTSG_PiterAdams_NN_21":
			dialog.text = "素晴らしい言葉だな、旦那！さあ、俺たちの相手、ラルフ・ファグルを紹介するぜ。\nそれから、こちらが俺たちのセコンド、フレデリック・ストークスだ。";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_22";
		break;
		
		case "DTSG_PiterAdams_NN_22":
			dialog.text = "「会ってくれ…」";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_23":
			dialog.text = "俺たちの相手、ラルフ・ファグルだ。";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_24":
			dialog.text = "「そしてこちらが我々の副官、フレデリック・ストークスだ。」";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_NN_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_NN_25":
			dialog.text = "...";
			link.l1 = "こいつがラルフか？普通の酔っ払いの隣人には見えねえな。";
			link.l1.go = "DTSG_PiterAdams_NN_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_NN_26":
			dialog.text = "隣にどんな奴がいるかなんて分からねえもんだぜ、考えたことあるか、ド・モール旦那？へっへっへ。";
			link.l1 = "なるほど、これは罠か……もう震えもしなくなったな。熱にうなされる芝居も飽きたってわけか？";
			link.l1.go = "DTSG_PiterAdams_NN_27";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_NN_27":
			dialog.text = "これから俺が振り払えるのは、お前の世間知らずさに笑うことだけだぜ。";
			link.l1 = "ほう、ほう。チャーリーがついて来たのだけが心残りだな――あんた一人なら、もっと楽に静かに片付けられたのによ…";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_21":
			dialog.text = "「おお、それは素晴らしいじゃねえか！」";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_22":
			dialog.text = "「ご紹介させてもらうぜ…」";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_23":
			dialog.text = "ストークスさん、副長。";
			link.l1 = "...";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_24":
			dialog.text = "「そして、こいつがラルフ・ファグルだ。」";
			link.l1 = "あれがラルフか？正直に言うと、もっと違う奴を想像してたぜ。\nだが関係ねえ、もっとひでえ連中も相手にしてきたからな。";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
			SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;
		
		case "DTSG_PiterAdams_Nastoroje_25":
			dialog.text = "ふむ、お前は何もわかっちゃいねえ世間知らずなのか？それとも、やけに自信過剰なのか？";
			link.l1 = "「俺が何を分かってねえってんだ、アダムズ旦那？さあ、驚かせてみろよ。」";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_Nastoroje_26":
			dialog.text = "普通はこういう状況じゃ人は驚いたり怯えたりするもんだが、あんたはちょっと違うタイプみてえだな。だが、 その自信満々な面をぶっ飛ばすのは、なおさら気分がいいぜ、ド・モール旦那。";
			link.l1 = "なんだと！？俺たちは同じ側じゃねえのか、ピーター？";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_27":
			dialog.text = "あの爺さんと一緒に俺たち全員を倒せるなんて思ってるんじゃねえだろうな。数で圧倒されてるぜ、旦那。";
			link.l1 = "俺が言った通り、わかってねえのはお前だ。チャーリーは少しぶつぶつ言ってたが、 念のために奴にみんなをここへ連れて来るように言っといたんだ。結果的に無駄じゃなかったな。\n野郎ども、こっちに来い！！！";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;
		
		case "DTSG_PiterAdams_Nastoroje_28":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
			DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);
			
			int DTSG_PoP_MK;
			if (MOD_SKILL_ENEMY_RATE == 2) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 4) DTSG_PoP_MK = 5;
			if (MOD_SKILL_ENEMY_RATE == 6) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 8) DTSG_PoP_MK = 4;
			if (MOD_SKILL_ENEMY_RATE == 10) DTSG_PoP_MK = 3;
			
			for (i=1; i<=DTSG_PoP_MK; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_"+i, "citiz_3"+i, "man", "man", sti(pchar.rank)-5, sti(pchar.nation), -1, false, "quest"));
				GiveItem2Character(sld, "blade_11");
				sld.equip.blade = "blade_11";
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
				LAi_SetHP(sld, 120.0, 120.0);
			}
		break;
		
		case "DTSG_PiterAdams_Nastoroje_29":
			dialog.text = "な、なんだと……";
			link.l1 = "驚いて怯えてるのか、アダムズ旦那？それはいいことだ。";
			link.l1.go = "DTSG_PiterAdams_BitvaDuel";
			SetCameraDialogMode(npchar);
		break;
		
		case "DTSG_PiterAdams_BitvaDuel":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("DTSG_PoP_Matrosy_"+i) != -1)
				{
					sld = CharacterFromID("DTSG_PoP_Matrosy_"+i);
					LAi_SetWarriorType(sld);
					LAi_CharacterDisableDialog(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			
			sld = CharacterFromID("Knippel");
			LAi_SetWarriorType(sld);
			LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("DTSG_PiterAdams");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("DTSG_RalfFaggl2");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;
		
		case "DTSG_Knippel_60":
			dialog.text = "そうやって嘘つきのろくでなしどもを始末すべきなんだ。\n王立海軍についてあんな嘘をつく度胸があったなんて、今でも信じられねえ！\nチェーンショットで首を締めてやりてえくらいだ…";
			link.l1 = "もう分かってるはずだろ、チャーリー。世の中には良心なんて持たねえ奴らがいるってな。俺が片付けるって言ったんだ、 お前は船に残っててもよかったんだぜ。『立派な連中』を助けるかどうか、俺を試したかったのか？それに、 思ったほど単純じゃなかったって、また俺の言った通りだったじゃねえか？";
			link.l1.go = "DTSG_Knippel_61";
		break;
		
		case "DTSG_Knippel_61":
			dialog.text = "お前だよ、旦那…";
			link.l1 = "その通りだ。だが教えてくれ、なぜ誰かがお前を狙うんだ？これが初めてじゃねえだろ。";
			link.l1.go = "DTSG_Knippel_62";
		break;
		
		case "DTSG_Knippel_62":
			dialog.text = "わからねえな、船長。年寄りのチャーリーはただの砲手だぜ。";
			link.l1 = "ふむ、なるほどな。よし、どうせあの哀れな決闘野郎どもは何の役にも立たねえもんしか持ってなかったしな……いや、アダムズの家で何か見つかるか見に行こうぜ。";
			link.l1.go = "DTSG_Knippel_63";
		break;
		
		case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;
		
		case "DTSG_Knippel_70":
			dialog.text = "そうか、この女も姿を消したか……あの「決闘」の直後に街から逃げる準備でもしてたのかもな？しかも急いでたんだろう――こんなに金を置いていくなんてよ！";
			link.l1 = "あんたの言う通りだ、置いていったのは金だけじゃねえ。もう一通手紙があるぜ。 急いでたから燃やすのを忘れたんだろうな。ほら、中身を見てみな、きっと気に入るぜ。";
			link.l1.go = "DTSG_Knippel_71";
		break;
		
		case "DTSG_Knippel_71":
			TakeItemFromCharacter(pchar, "letter_1");
			dialog.text = "（読み上げる）まあ、「年寄り」ってのは異議ありだな。";
			link.l1 = "今はそんなことどうでもいいだろう。これで二度目だぜ、あんたを狙って傭兵を送り込んできて、 しかも金と情報まで与えてやがる。しかも、狙いはあんただけだ。教えてくれよ、ただの砲手のお前が、 いったい誰をそこまで怒らせたんだ？\n";
			link.l1.go = "DTSG_Knippel_72";
		break;
		
		case "DTSG_Knippel_72":
			dialog.text = "俺には一つだけ考えがあるんだ、旦那、本当にそれが当たってほしくねえんだよ。";
			link.l1 = "そうか、じゃあ本当のことなんだろうな。はっきり言えよ。";
			link.l1.go = "DTSG_Knippel_73";
		break;
		
		case "DTSG_Knippel_73":
			dialog.text = "昔、セントジョンズでいろんな奴らに借金があってな、そして…";
			link.l1 = "…で、今度は自分が狙われてると思ってるのか？傭兵なんか雇える奴がどれだけいると思うんだ？";
			link.l1.go = "DTSG_Knippel_74";
		break;
		
		case "DTSG_Knippel_74":
			dialog.text = "考え方は正しいぜ、旦那。結局、俺はほとんどの借金を金貸しから借りて返したんだ。あいつなら、 こんなこと全部余裕でできるさ。だが……";
			link.l1 = "「でも何だ？借金は俺たちが払う、それで終わりだろう。何がそんなに気になるんだ？」";
			link.l1.go = "DTSG_Knippel_75";
		break;
		
		case "DTSG_Knippel_75":
			dialog.text = "わかるだろう、船長。リチャードが俺の代わりに払ってくれるって約束してくれたんだ。";
			link.l1 = "あいつがやらなかったとでも思うのか？";
			link.l1.go = "DTSG_Knippel_76";
		break;
		
		case "DTSG_Knippel_76":
			dialog.text = "もう何を考えればいいのかわからねえ、旦那。俺たちが知り合ってた間、あいつは模範的な紳士だと思ってたんだ。\nだが、あいつがあんたを置いてアビゲイルと逃げた後じゃ……驚きゃしねえさ。だからこそ、俺はそれが本当であってほしくねえって言ったんだ。";
			link.l1 = "推測はまず確かめてから怒れ、チャーリー。\n行くぞ、セントジョンズにもう一度行くんだ。";
			link.l1.go = "DTSG_Knippel_77";
		break;
		
		case "DTSG_Knippel_77":			//КОНЕЦ ЭТАПА 2
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			n = Findlocation("PortPax_town");
			locations[n].reload.l31.name = "houseF1";
			locations[n].reload.l31.go = "CommonRoom_MH9";
			locations[n].reload.l31.emerge = "reload1";
			locations[n].reload.l31.autoreload = "0";
			locations[n].reload.l31.label = "House";
			
			BackItemName("letter_1");
			BackItemDescribe("letter_1");
			AddQuestRecord("DTSG", "6");
			QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
			
			AddMapQuestMarkCity("SentJons", true);
			PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
			PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
			PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;
		
		case "DTSG_Knippel_PoPDuelTime":
			dialog.text = "船長！！！";
			link.l1 = "どうした、チャーリー、何があったんだ？";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_2":
			dialog.text = "何があったって！？まさか決闘のことを忘れたんじゃねえだろ、旦那！アダムズはもう斬り刻まれてるかもしれねえのに、 あんたはここでのんびりしてるのかよ！\n";
			link.l1 = "よしっ！…すぐに町を出るぜ。";
			link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;
		
		case "DTSG_Knippel_PoPDuelTime_3":
			DialogExit();
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;
		
		case "DTSG_AntiguaArest":
			dialog.text = "「シャルル・ド・モール船長か？そっちはチャーリー・クニッペルじゃねえか？」";
			link.l1 = "いや、これは……";
			link.l1.go = "DTSG_AntiguaArest_2";
		break;
		
		case "DTSG_AntiguaArest_2":
			dialog.text = "否定するなよ、旦那――この植民地じゃ誰もがチャーリーを知ってるんだぜ。";
			link.l1 = "じゃあ、なんで聞くんだ？どう手を貸せばいい？";
			link.l1.go = "DTSG_AntiguaArest_3";
		break;
		
		case "DTSG_AntiguaArest_3":
			dialog.text = "できません。どうか抵抗しないでください――チャーリーはここで指名手配されています。彼を拘束しなければなりません。";
			link.l1 = "俺の部下にどんな罪状があるのか教えてもらえるか？借金のせいか？だったら、俺が肩代わりしてやる。今すぐ、 あんたの目の前で銀行家のところへ行こうじゃねえか。\n";
			link.l1.go = "DTSG_AntiguaArest_4";
		break;
		
		case "DTSG_AntiguaArest_4":
			dialog.text = "借金だと？そんな話、初耳だぜ。詳しいことは知らねえが、頼むから話をややこしくしないでくれ――俺はただ命令に従ってるだけなんだ。";
			link.l1 = "「ああ、こりゃまったく最高だな……」";
			link.l1.go = "DTSG_AntiguaArest_5";
		break;
		
		case "DTSG_AntiguaArest_5":
			StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;
		
		case "DTSG_AntiguaArest_6":
			dialog.text = "船長……";
			link.l1 = "チャーリー、今逃げたら俺たちの首にかかる賞金はもっと高くなるぜ。しかも、力ずくで突破なんてできやしねえだろ？ 俺が何とかお前を助け出してみせるから、無茶だけはするなよ！";
			link.l1.go = "DTSG_AntiguaArest_7";
		break;
		
		case "DTSG_AntiguaArest_7":
			DialogExit();
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "8");
			pchar.questTemp.DTSG_KnippelDolg = true;
			
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("DTSG_AntiguaSold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
				sld.location = "None";
			}
		break;
		
		case "DTSG_AntiguaStrazhBank":
			dialog.text = "今すぐ騒ぐのとこの男を脅すのをやめろ、旦那。武器を渡して、ただちに俺について来い！";
			link.l1 = "俺は誰も脅してねえ、何かの間違いだ。これは商売の話であって、殺人未遂なんかじゃねえぞ。";
			link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;
		
		case "DTSG_AntiguaStrazhBank_2":
			dialog.text = "俺にはそうは見えねえな。お前は法に裁かれることになるぜ。";
			link.l1 = "謝って立ち去ったらどうなるんだ？";
			link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;
		
		case "DTSG_AntiguaStrazhBank_3":
			dialog.text = "俺が邪魔したことを、こっそり戻ってきて仕上げるつもりか？俺をバカだと思ってんのか？";
			link.l1 = "穏便に済ませたくないなら、そうするしかねえな。神のみぞ知るが、俺だってこんな事態にはしたくなかったんだ…";
			link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;
		
		case "DTSG_AntiguaStrazhBank_4":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki":
			dialog.text = "お前があいつを殺したんだな！..";
			link.l1 = "自分の手でやったと思え、旦那。俺の質問にちゃんと答えりゃ、そんなに取り乱すこともなかっただろうが。 誓って言うが、もう一声でも叫んだら頭を吹き飛ばすぞ。";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
			link.l2 = "ああ、俺が殺したんだ。無理やりやらされたんだよ。だが、あんたはあいつみたいな脳なしじゃねえし、 同じ真似はしないよな？";
			link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V1":
			dialog.text = "何の用だ！？";
			link.l1 = "少し前にチャーリー・ニッペルがあなたから金を借りた。彼の友人が借金を返すと約束したが、 どうやら果たされていないようだ。これ以上俺たちに傭兵を差し向けるのは今すぐやめてくれ。もし払えるなら、 今ここでチャーリーの借金を肩代わりするつもりだ。";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexLandExpToScill(100, 0, 0);
			AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_V2":
			dialog.text = "何の用だ！？";
			link.l1 = "少し前にチャーリー・クニッペルがあなたから金を借りた。彼の友人が借金を返すと約束したが、 どうやら果たされていないようだ。これ以上俺たちに傭兵を差し向けるのは今すぐやめてくれ。もし払えるなら、 今ここでチャーリーの借金を俺が返すつもりだ。";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_3":
			dialog.text = "「チャーリー！？俺があいつにそんなことするわけねえだろ。あいつは誠実で正直な男だ。それに、 借金なんざとっくに返し終わってる。ヴァルキリー号の船長、 フリートウッド旦那が最後のペソまできっちり清算したんだ。」";
			link.l1 = "本当か？あいつが誰か知ってるぜ。最初からそう言ってくれりゃよかったんだ。面倒かけて悪かったな、じゃあな。";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_4":
			dialog.text = "そんな簡単に！？お前は俺を脅したんだぞ！それに人まで殺したじゃねえか…";
			link.l1 = "俺の言ったことを忘れたのか？もう一声でも上げたら、あいつの仲間入りだぜ。じゃあな。";
			link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;
		
		case "DTSG_AntiguaUsurer_PosleDraki_5":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			npchar.dialog.filename = "Usurer_dialog.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetOwnerType(npchar);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			
			chrDisableReloadToLocation = false;
			AddQuestRecord("DTSG", "9");
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;
		
		case "DTSG_Killer":
			dialog.text = "まだここにいて、まだ首を吊ってねえのか？まあ、サセックス号からの挨拶だ、チャーリー。";
			link.l1 = "あんたが誰であろうと、挨拶するぜ。";
			link.l1.go = "DTSG_Killer_2";
			CharacterTurnToLoc(npchar, "goto", "goto9");
		break;
		
		case "DTSG_Killer_2":
			dialog.text = "ああ、シャルル・ド・モール。わしのところに来てくれてありがたいのう、チャーリーはずっと待っておったんじゃ。 頼りにしとったぞ。";
			link.l1 = "俺たちは誰だ？";
			link.l1.go = "DTSG_Killer_3";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "DTSG_Killer_3":
			dialog.text = "関係ねえよ。あんたのせいで、俺たちは大事な時間と金を失ったんだ、de Maure旦那。ここでチャーリーもあんたもまとめて片付けちまっても、誰も文句は言わねえだろうさ。";
			link.l1 = "まあ、どうせ俺たちはもう死んじまったんだ、せめて心優しく、 俺たちが一体誰をそんなに怒らせちまったのか教えてくれねえか？\nもう二度とやらねえって約束するぜ。\nそれと、サセックスってのは誰だ？";
			link.l1.go = "DTSG_Killer_4";
		break;
		
		case "DTSG_Killer_4":
			dialog.text = "無理だな。任務があるしな、お前と違って、俺は口先じゃなくて行動の男なんだぜ。";
			link.l1 = "頼むから、一体何が起きてるのか誰か説明してくれねえのか！？";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Killer_5");
		break;
		
		case "DTSG_KnippelDaySpasen":
			dialog.text = "なんてこった、船長、ここでとんでもねえ虐殺をやらかしたじゃねえか！";
			link.l1 = "異議があるのか？絞首台の方がいいのか？それとも、ここで永遠に朽ち果てたいのか？";
			link.l1.go = "DTSG_KnippelDaySpasen_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_KnippelDaySpasen_2":
			dialog.text = "いいえ、旦那。助けてくれて感謝するぜ。正直言って、あんたが来てくれるとは思わなかった。 俺をあっさり連中に渡したからな。それに、見張りを簡単に片付けたのにも驚いたぜ――あいつはシーフォックス、海兵だったんだ。";
			link.l1 = "言っただろ、俺が助けるって。疑うんじゃなかったんだ。さあ、衛兵どもが来る前にこの牢屋から出ろ。";
			link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;
		
		case "DTSG_KnippelDaySpasen_3":
			dialog.text = "あいよ、船長。";
			link.l1 = "...";
			link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;
		
		case "DTSG_KnippelDaySpasen_4":
			DialogExit();
			
			Pchar.GenQuest.Hunter2Pause = true;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;
		
		case "DTSG_KnippelDaySpasen_5":
			dialog.text = "くそっ、旦那、信じられねえよ……";
			link.l1 = "ところで、教えてくれ、何の罪で訴えられたんだ？それと、サセックスって誰だ？";
			link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;
		
		case "DTSG_KnippelDaySpasen_6":
			dialog.text = "わからねえ、旦那。誰のことを言ってたのか、俺にはさっぱり見当もつかねえ…";
			link.l1 = "よし、後で確かめよう。今はここから脱出しなきゃならねえ。";
			link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;
		
		case "DTSG_KnippelDaySpasen_7":
			DialogExit();
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddPassenger(pchar, npchar, false);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			AddQuestRecord("DTSG", "12");
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_AntiguaNightPirs":
			dialog.text = "次はどうするんだ、旦那？あの吸血鬼野郎を白昼堂々ぶちのめすなんて、命知らずな真似だぜ。";
			link.l1 = "今、いい考えが浮かんだぜ。どうして昼間にあいつをぶちのめす必要がある？今、 この夜の闇に紛れてやっちまえばいいじゃねえか？";
			link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;
		
		case "DTSG_AntiguaNightPirs_2":
			dialog.text = "畜生、そりゃあ見事な考えだぜ、船長！";
			link.l1 = "その通りだ。チャーリー、ちょっと聞くが、お前はここにしばらく住んでたんだろう。 金貸しがどこに住んでるか知ってるか？";
			link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;
		
		case "DTSG_AntiguaNightPirs_3":
			dialog.text = "昔は知ってたんだがな、旦那、前回来たときは家を売りに出してたんだ。新しい家がどこかは全然わからねえ。";
			link.l1 = "「うーん、そりゃ困ったな……」";
			link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;
		
		case "DTSG_AntiguaNightPirs_4":
			dialog.text = "きっと何とかなるさ、船長。何しろ、あの恐ろしいルーカス・ローデンブルクを倒したんだからな！";
			link.l2 = "よし、俺がやるぜ。だが、もし金貸しの家がどこか知ってたら、もっと助かったんだがな！";
			link.l2.go = "DTSG_AntiguaIskat_1";
			link.l1 = "ああ、そうしたさ。でもな、朝の方が夜より賢いんだ、チャーリー。旅の疲れを癒やして、昼間に行こうぜ――俺たちはあの男を殺しに来たわけじゃねえんだからな。\n";
			link.l1.go = "DTSG_AntiguaSpat_1";
		break;
		
		case "DTSG_AntiguaSpat_1":
			dialog.text = "本当にそれでいいんですか、旦那？奇襲の利点を失っちまいますぜ。";
			link.l1 = "俺は確信してるし、もう疲れたんだ。\nそれに、ただ話がしたいだけさ。必要なら、ちょっと脅かしてやるだけでいい。";
			link.l1.go = "DTSG_AntiguaSpat_2";
		break;
		
		case "DTSG_AntiguaSpat_2":
			TavernWaitDate("wait_day");
			DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;
		
		case "DTSG_AntiguaIskat_1":
			dialog.text = "知らねえことは知らねえんだ、悪いな、旦那。";
			link.l1 = "ああ、気にするな、探しに行こうぜ。";
			link.l1.go = "DTSG_AntiguaIskat_2";
		break;
		
		case "DTSG_AntiguaIskat_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			AddQuestRecord("DTSG", "13");
			pchar.questTemp.DTSG_NightIskat = true;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.GenQuest.CannotWait = true;
			pchar.questTemp.TimeLock = true;
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood":
			dialog.text = "「俺と同じことを考えてるのかい、旦那？」";
			link.l1 = "残念ながらそうだ、チャーリー。カリブ海にその名前の有名な船長は他にいないし、リチャードもロンドンに行ったんだ。 だから、偶然とは考えにくいな。";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_2":
			dialog.text = "ひどい……あいつのことをきつく言ったことはあるが、こんな目に遭ってほしいなんて思ったことは一度もねえ！それに、 かわいそうなアビィ！……あいつは子どもを身ごもってたんだ。どうか無事でいてくれよ……";
			link.l1 = "ああ、まったくだ、誰にもこんな目に遭ってほしくねえよ。アビーが無事だといいがな。 ディックにこんなことをした奴に心当たりはあるか？あいつが話してた強い敵とか、いなかったか？";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_3":
			dialog.text = "冗談だろう、船長。ヨーロッパのことは知らねえが、ここじゃどのオランダ野郎もリチャードの死を望んでたんだぜ。";
			link.l1 = "そうだな。もしかすると、ここにいる誰かが大金を使って、奴に刺客を旧世界へ送り込んだのかもしれねえ。 お前を襲ってるのは、このしみったれた金貸しじゃなくて、リチャードの謎の敵って可能性もあるんじゃねえか？\n";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_4":
			dialog.text = "わからねえな、旦那。今となっちゃ、何だってあり得るぜ。だが、 そうなると俺たち全員が面倒なことになるんじゃねえか…";
			link.l1 = "ああ、そうだな、俺もこんな可能性は気に入らねえよ。";
			link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;
		
		case "DTSG_Knippel_SluhSmertFleetWood_5":
			DialogExit();
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "14");
			pchar.questTemp.DTSG_Nastoroje2 = true;
			chrDisableReloadToLocation = false;
			
			PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
			PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;
		
		case "DTSG_NightRostovshik":
			dialog.text = "何だ、誰だ…何だと！？何が起きてるんだ…？お前は誰だ！？";
			link.l1 = "おいおい、冗談じゃねえ。もしお前を殺したかったら、寝てる間にやってるさ。だから、 余計なことして命を縮めるのはやめようぜ。わかったら頷け。";
			link.l1.go = "DTSG_NightRostovshik_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_NightRostovshik_2":
			dialog.text = "「うん……」";
			link.l1 = "よしよし。落ち着け――俺はお前を盗んだり、誘拐したり、傷つけたりしに来たわけじゃねえ。";
			link.l1.go = "DTSG_NightRostovshik_3";
		break;
		
		case "DTSG_NightRostovshik_3":
			dialog.text = "じゃあ…なんでここにいるんだ？なぜ朝に来られなかったんだ？";
			link.l1 = "「裕福で影響力のある誰かが俺の友人を狙っているからだ。\nお前がその人物だと疑う理由がある。だから、あいつが白昼堂々この通りを歩くのは危険だろうな。」";
			link.l1.go = "DTSG_NightRostovshik_4";
		break;
		
		case "DTSG_NightRostovshik_4":
			dialog.text = "だが本当に何の話をしてるのか分からねえんだ、旦那…";
			link.l1 = "チャーリー・クニッペル。町のみんながあいつを知ってるぞ。よく考えてみろ。あいつはお前に借金があるんだ。";
			link.l1.go = "DTSG_NightRostovshik_5";
		break;
		
		case "DTSG_NightRostovshik_5":
			dialog.text = "俺たちの古株チャーリーのことか？？それは本当だが、あいつの借りはずっと前に返されたんだ、 ただし本人じゃなくてな。";
			link.l1 = "「それで、その恩人って誰だったんだ？」";
			link.l1.go = "DTSG_NightRostovshik_6";
		break;
		
		case "DTSG_NightRostovshik_6":
			dialog.text = "あいつの船長はリチャード・フリートウッド卿だ。信じられねえなら、俺の記録を見せてやるぜ。";
			link.l1 = "「フリートウッドだと？なら信じるぜ。じゃあ、チャーリーを追わせるために傭兵を送り込んだわけじゃねえんだな？」";
			link.l1.go = "DTSG_NightRostovshik_7";
		break;
		
		case "DTSG_NightRostovshik_7":
			dialog.text = "もちろんそんなことはしねえさ、なんで俺がそんなことをするんだ？？それに教えてくれよ、 それにどんな意味があるってんだ？";
			link.l1 = "確かに。さて、遅くに訪ねてすまなかったな。おやすみ。";
			link.l1.go = "DTSG_NightRostovshik_8";
		break;
		
		case "DTSG_NightRostovshik_8":
			DialogExit();
			
			PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
			PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";
			
			LAi_CharacterDisableDialog(npchar);
			Pchar.GenQuest.Hunter2Pause = true;
			AddQuestRecord("DTSG", "15");
		break;
		
		case "DTSG_NightKiller":
			dialog.text = "なんだ、チャーリー、今夜は昔の旦那のところにでも隠れようと思ったのか？あいつはもういねえよ。だが、 すぐに会えるさ。サセックス号からのご挨拶だ。";
			link.l1 = "それはもう知ってたぜ。で、サセックスって誰だ？それに、お前は何者だ？";
			link.l1.go = "DTSG_NightKiller_2";
		break;
		
		case "DTSG_NightKiller_2":
			dialog.text = "それはお前の知ったことじゃねえ、ド・モール旦那。もっと関わってほしくなかったのに、残念だぜ。お前は厄介者だ。";
			link.l1 = "誰にとっての迷惑だ？まさか、 俺がとんでもなく権力のある怒り狂ったイギリス野郎の女房と寝ちまったなんて言わないでくれよ。";
			link.l1.go = "DTSG_NightKiller_3";
		break;
		
		case "DTSG_NightKiller_3":
			dialog.text = "面白いじゃねえか。冗談を言う暇があるとはな。どうやらお前について聞いた噂は本当みたいだな\n俺たちが欲しいものは何だ？チャーリーの首さえあれば十分だが、 今までお前が俺たちにどれだけ迷惑をかけてきたかを考えると、今回はお前も無関係じゃねえ――余計なことに首を突っ込んでばかりいるからな。";
			link.l1 = "俺たちは逮捕されたってことか？";
			link.l1.go = "DTSG_NightKiller_4";
		break;
		
		case "DTSG_NightKiller_4":
			dialog.text = "逮捕だと？いや、旦那、もう生ぬるい手段は終わりだ。これは処刑だぜ、ド・モール船長。";
			link.l1 = "同感だ。問題は、誰のものかってことだけだな。";
			link.l1.go = "DTSG_NightKiller_5";
		break;
		
		case "DTSG_NightKiller_5":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DTSG_Killers_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;
		
		case "DTSG_Knippel_80":
			dialog.text = "シーフォックスが関わっているとは思わなかったぜ…";
			link.l1 = "まあ、何事にも初めてはあるもんだ。で、チャーリー、サセックスって誰だ？";
			link.l1.go = "DTSG_Knippel_81";
		break;
		
		case "DTSG_Knippel_81":
			dialog.text = "俺は……";
			link.l1 = "これがどれだけ深刻になってるか分からねえのか？それに、チャーリー、俺たちは同じ立場だろう。 だから詳しい話を聞く権利があるはずだ。";
			link.l1.go = "DTSG_Knippel_82";
		break;
		
		case "DTSG_Knippel_82":
			dialog.text = "もちろんだぜ、船長。でもここじゃないよな？島を出て、船の上で話そうぜ。";
			link.l1 = "あんたの言う通りだ。よし、急ごう。";
			link.l1.go = "DTSG_Knippel_83";
		break;
		
		case "DTSG_Knippel_83":
			DialogExit();
			AddQuestRecord("DTSG", "16");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			chrDisableReloadToLocation = false;
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom":
			dialog.text = "呼んだかい、船長？";
			link.l1 = "ああ、チャーリー。話があるんだ。もう何についてか察してるだろう。";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
			//LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_2":
			dialog.text = "ああ、旦那……";
			link.l1 = "よし。お前が犯罪者でもなんでもねえのに、どうして同胞たち――しかも精鋭部隊まで――がお前を追い回してるのか、理由を聞かせてくれ。";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_3":
			dialog.text = "俺には本当に分からねえんだ、旦那…";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "冗談じゃねえぞ、チャーリー。お前を狙ってる奴は、海の狐どもに命令できるやつだ。リチャードの殺しも、 そいつの仕業かもしれねえ。だから、何か心当たりがあるなら話してくれ。サセックスからの挨拶ってのは何だ？ そいつは誰なんだ？";
			}
			else
			{
				link.l1 = "よそ見するな、チャーリー。何か知ってるんだろう。\n俺はお前の船長だ、全部話せと命じる。\nサセックスって誰だ？";
			}
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_4":
			dialog.text = "わかったぜ、船長。サセックスは人じゃねえ。……船なんだ。";
			link.l1 = "「船からの挨拶だと？そんな馬鹿な話があるか。」";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_5":
			dialog.text = "説明させてくれ。座ってもいいか、旦那？話は長くて、あまり愉快なもんじゃねえんだ。";
			link.l1 = "もちろんだ、チャーリー。やってくれ。";
			link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;
		
		case "DTSG_KnippelRazgovorOProshlom_6":
			DialogExit();
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Knippel"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			SetLaunchFrameFormParam(StringFromKey("Knippel_11", NewStr()), "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
			LaunchFrameForm();
			//DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;
		
		case "DTSG_Kurier":
			dialog.text = "「おい、チャーリー、俺はフリートウッド船長から来たんだ。あんたに会いたいってさ。」";
			link.l1 = "ありがとな、相棒。何かあったのか？普段なら、あいつは全部すぐにお前を通して伝えてくるだろうに。";
			link.l1.go = "DTSG_Kurier_2";
		break;
		
		case "DTSG_Kurier_2":
			dialog.text = "わからねえ。あいつはお前と直接話したいって言ってるんだ。お前の問題だ、自分たちで片付けろよ。";
			link.l1 = "ああ、嫌な予感がするんだが…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Kurier_3");
		break;
		
		case "DTSG_Cortny":
			dialog.text = "...";
			link.l1 = "おやすみ、旦那！";
			link.l1.go = "DTSG_Cortny_2";
		break;
		
		case "DTSG_Cortny_2":
			dialog.text = "おやすみ。通してくれ。";
			link.l1 = "もちろんだ、どうぞ、すまねえな、旦那。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Cortny_3");
		break;
		
		case "DTSG_Fleetwood":
			dialog.text = "「ああ、チャーリー、お前か。入れ、入れ。後ろの扉を閉めてくれ。」";
			link.l1 = "おやすみなさい、船長。何が起きてるんだ？それに、あの男は誰だ？偉そうな孔雀め……";
			link.l1.go = "DTSG_Fleetwood_2";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_Fleetwood_2":
			dialog.text = "それは言えねえな。それに、この話を誰かに聞かれるわけにもいかねえ。誰にも話すんじゃねえぞ、わかったか？";
			link.l1 = "ああ、旦那。何かあったのか？いつになく心配そうじゃねえか、あんたらしくねえな。";
			link.l1.go = "DTSG_Fleetwood_3";
		break;
		
		case "DTSG_Fleetwood_3":
			dialog.text = "そう見えるかもしれねえな。お前さんもあんまりいい顔じゃねえぜ――夜だからな。だが、今夜はもう眠ってられねえぞ、相棒――緊急かつ極秘の任務があるんだ。\n";
			link.l1 = "「それで、何をすることになるんだ、船長？」";
			link.l1.go = "DTSG_Fleetwood_4";
		break;
		
		case "DTSG_Fleetwood_4":
			dialog.text = "裏切り者の始末だ。しかも、俺たち自身の中からな。\nまもなく、ドミニカ沖に本国からの外交船が現れる――フリゲート艦「サセックス」だ。\n表向きは、オランダと有利な取引を交渉するために来ることになっている。だが、実際は……";
			link.l1 = "「……奴らが敵に情報を渡すつもりじゃねえか、旦那？」";
			link.l1.go = "DTSG_Fleetwood_5";
		break;
		
		case "DTSG_Fleetwood_5":
			dialog.text = "さらに悪いぜ。完全にあっち側に寝返ったってわけだ。大西洋を渡ってきたばかりで奴らはくたびれてるだろうが、 あいつらのフリゲートは上等な船だ、こっちが重い船で攻撃すりゃ、きっと逃げようとするだろうよ\nだからこそ、素早く決断して動かねえといけねえ。頼れるのは“ヴァルキリー”だけだ――あの船だけがこの任務をこなせるんだ。";
			link.l1 = "古い“ヴァルキリー”でフリゲートを扱えるかねえ……";
			link.l1.go = "DTSG_Fleetwood_6";
		break;
		
		case "DTSG_Fleetwood_6":
			dialog.text = "ははは、チャーリー、お前は自分の船長を疑ってるのか？それに、言っただろう、奴らはくたくたになってる。 俺たちが奇襲をかければ、有利なのは全部こっちだぜ。\n";
			link.l1 = "俺は絶対にそんなことしねえ！だが、旦那……自分が何をしてるか分かってるんだろうな……";
			link.l1.go = "DTSG_Fleetwood_7";
		break;
		
		case "DTSG_Fleetwood_7":
			dialog.text = "俺は確信してるぜ。もう一つ言っておく。あの裏切り者は議会の中でも高い地位にいるんだ、わかるか？ やつはどこにでも目と耳を持ってるかもしれねえ――本国だけじゃなく、もうこのカリブにもな。だから、サセックス号や俺たちの任務の詳細は、町じゃ絶対に口にするなよ。 \n";
			link.l1 = "言われなくても分かってるぜ、旦那。いつだってこのチャーリーじいさんに任せときな。";
			link.l1.go = "DTSG_Fleetwood_8";
		break;
		
		case "DTSG_Fleetwood_8":
			dialog.text = "わかってるさ。だが、今回は今まで以上に賭け金がでかいんだ。荷物をまとめて準備しろ――夜明けに出航するぞ。";
			link.l1 = "ああ、旦那。おやすみ、旦那。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_9");
		break;
		
		case "DTSG_Knippel_SamSoboi":
			dialog.text = "リチャードがこんなふうなのは初めて見たぜ…あいつ、すごく心配してたし、いや…もしかして怖がってたのか？";
			link.l1 = "「でも、なぜだ？俺にはその話すらしてくれなかった。まあ、いいさ。あいつは素晴らしい船長だ、 このフリゲートと疲れた乗組員もうまくやっていけるだろう。」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Knippel_SamSoboi_2");
			DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;
		
		case "DTSG_Fleetwood_10":
			dialog.text = "「サセックス号」が水平線に見えるぞ、チャーリー、準備しろ。";
			link.l1 = "いつでも準備万端だぜ、船長。";
			link.l1.go = "DTSG_Fleetwood_11";
		break;
		
		case "DTSG_Fleetwood_11":
			dialog.text = "よし、頼りにしてるぜ、お前とお前のチェーンショットにな。できるだけ早くあいつらの帆をズタズタにしてくれ、 できればマストをへし折ってやれ。沈めるために無理して戦うのは意味がねえから、俺は拿捕を狙うつもりだ\nそれに、裏切り者が確実に死んだか確認しなきゃならねえ――もし沈めちまったら、結局近づいて誰も生き残ってねえか確かめる羽目になるからな。";
			link.l1 = "「たった一人の裏切り者のために、こんなにも多くの同胞を殺すなんて……」";
			link.l1.go = "DTSG_Fleetwood_12";
		break;
		
		case "DTSG_Fleetwood_12":
			dialog.text = "残念だ。俺もつらいよ、チャーリー。でも命令は命令だ。少なくとも遊びでやってるわけじゃねえ。 だからさっさと片付けようぜ。";
			link.l1 = "ああ、旦那……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Fleetwood_13");
		break;
		
		case "DTSG_Graf_Sheffild_1":
			dialog.text = "もういい！俺は剣を差し出して、お前の要求について話し合う用意がある。\nだがまず、名を名乗れ！お前は何者だ、そしてどうして俺たちを襲うんだ！？\nこれは反逆だぞ！";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_3":
			dialog.text = "リチャード・フリートウッド船長。で、お前がシェフィールド伯爵か？それに、まったくその通りだ、これは反逆だぜ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_5";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_5":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_6":
			dialog.text = "俺が誰か知ってるのか？くそっ！こうなることは分かってたぜ、どこもかしこもネズミだらけだ、だから俺は頼んだんだ、 いや、戦艦をくれって懇願までしたんだよ…";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_7";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_7":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_8":
			dialog.text = "それで助かったわけじゃねえ、ただ避けられぬ運命を少し引き延ばすだけさ。どうせ俺は別の手を考えただろうしな。\nそれからな、裏切りってのはお前のことだ、シェフィールド伯。";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_9";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_9":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_10":
			dialog.text = "じゃあ、俺のことなんか何も知らねえんだな、旦那！イングランドに俺ほど忠義を尽くす男はいねえって、 みんな知ってるぜ！この間違い、きっと後悔することになるから覚えておけよ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_12";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_12":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_13":
			dialog.text = "俺は何も後悔しちゃいねえ、オランダ野郎に寝返るのは俺じゃねえからな。";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
		case "DTSG_Graf_Sheffild_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Graf_Sheffild");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_16":
			dialog.text = "なにっ！？何を馬鹿なこと言ってやがる！？お前は騙されて、狂った猟犬みてえに間違った跡を追ってきたんだぞ\nゴホン、確かに俺はオランダ西インド会社との交渉に向かってる。だが、それも我らがイングランドのためだ、船長。 このままじゃ大変な間違いになるが、まだ修正できるはずだ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_17";
			CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
		case "DTSG_Graf_Sheffild_17":
			DialogExit();
			sld = CharacterFromID("Fleetwood");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Graf_Sheffild_18":
			dialog.text = "俺の一存じゃ決められねえんだ。ましてや、お前らの意志でもない。野郎ども、あんたらは間違った側を選んじまったな。 さらばだ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Graf_Sheffild_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

		case "DTSG_Graf_Sheffild_19":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Fleetwood");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;
		
		case "DTSG_Graf_Sheffild_22":
			dialog.text = "ここはもう終わりだな。あのデブ野郎、いつまでもギャーギャー騒いでると思ったぜ。まったく、伯爵様ってのはよ、 なあ、チャーリー？";
			link.l1 = "ただ気になるんだ、旦那、もし大佐が間違っていたらどうする？それとも、まさかとは思うが、 伯爵を始末するために俺たちに嘘をついたとしたら？";
			link.l1.go = "DTSG_Graf_Sheffild_23";
		break;
		
		case "DTSG_Graf_Sheffild_23":
			dialog.text = "俺の話をよく聞け、相棒。それも、しっかりとな。俺たちの務めは、どこから見ても危険で厳しいもんだ。 何が起きてもおかしくねえ――悲惨なミス、馬鹿げた偶然、あるいは裏切りの罠だってな\n国に仕えるってのは、ただ砲弾を大砲に詰め込むだけじゃねえんだ、チャーリー。偉い連中にとっちゃ、 厳しい決断を下すことだ。そして俺たちみたいな兵士には、その決断を実行することなんだよ。";
			link.l1 = "だがよ、もし俺たちがいつか無実の者の血を流しちまったらどうするんだ、船長？それは全部、 俺たち自身の手と良心に背負うことになるんだぜ。";
			link.l1.go = "DTSG_Graf_Sheffild_24";
		break;
		
		case "DTSG_Graf_Sheffild_24":
			dialog.text = "ならば、血は俺たちだけじゃなく、あいつらの手にも付くことになるさ。いや、むしろあいつらの方が重いかもしれねえ。 それを慰めにしろよ。大事なのは、俺たちの意志は純粋だったってことだ――祖国の敵を排除するためにな。\nさあ、手を貸してくれ、チャーリー。まだオランダの襲撃に見せかける必要があるんだ。";
			link.l1 = "ああ、旦那……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_Graf_Sheffild_25");
		break;
		
		case "DTSG_Knippel_101":
			dialog.text = "だから、オランダ人の仕業に見せかけるために偽の証拠を残したんだ。\nあの日のことは、リチャードと俺は二度と口にしなかった。";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "なるほど、今なら色々と納得がいくぜ。リチャードの死の裏には伯爵の親族か取り巻きがいるんだろうな。\nだが、なぜお前が狙われる？お前はただの砲手で、あの日に決断を下したわけじゃねえだろう。";
				link.l1.go = "DTSG_Knippel_ZS_102";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "確かに。これは厄介な話で、鼻につくぜ。誰かが知って、伯爵の仇討ちを決めたのかもしれねえ。だが、 たかが一人の砲手のために、そこまで金や傭兵、シーフォックスまで雇うなんてありえねえよ、チャーリー。";
				link.l1.go = "DTSG_Knippel_NS_102";
			}
		break;
		
		case "DTSG_Knippel_ZS_102":
			dialog.text = "もしかすると、こいつはリチャードの元乗組員を全員狙ってるのかもしれねえ。どう思う、旦那？";
			link.l1 = "俺たちはアンティグアから距離を取るべきだと思うぜ、早ければ早いほどいい。";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_NS_102":
			dialog.text = "俺もその問いを自分に投げかけたことがあるんだが、船長、答えはまだ見つかっちゃいねえ。";
			link.l1 = "くそっ。誰か来やがった。邪魔するなって言っただろうが！";
			link.l1.go = "DTSG_Knippel_103";
		break;
		
		case "DTSG_Knippel_103":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Knippel_103");
		break;
		
		case "DTSG_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "チャールズ！…";
				link.l1 = "どうしたんだ、ヘレン？？";
				link.l1.go = "DTSG_Helena_2";
			}
			else
			{
				dialog.text = "「チャールズ、あんたに“誰も入れるな、俺とチャーリーを邪魔するな”って言われたのは覚えてるが……」";
				link.l1 = "…自分で来ることにしたんだな。よしよし、大丈夫だ、ヘレン。";
				link.l1.go = "DTSG_Helena_2";
			}
		break;
		
		case "DTSG_Helena_2":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "イギリスの軍艦だ！少し前に目撃されたんだ。最初は気にしなかったが、もうすぐこっちに到着しちまうぞ！ あんな速い船は見たことがねえ。";
				link.l1 = "それなら教えてくれて感謝する。奴が近づく前に準備する時間があるといいが。ヘレン、チャーリー、戦闘配置につけ！";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
			else
			{
				dialog.text = "…密談は後で続ければいいだろう。イギリスの軍艦がこっちに向かってるんだ。大事なことだと思ってな。";
				link.l1 = "よし、ちょっと見てくるぜ。ありがとう、ヘレン。";
				link.l1.go = "DTSG_GotovimsyKBitve";
			}
		break;
		
		case "DTSG_Tichingitu_1":
			dialog.text = "船長、速い船がこっちに向かってきてるぜ。すごい速さだ。奴らの魂は悪意を秘めてると、精霊が俺に囁いてるんだ。";
			link.l1 = "警告してくれて、あんたと精霊たちに感謝するぜ。念のため戦闘の準備をしとけ。\nそれから、この伝言を他の連中にも伝えてくれよ。";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_Alonso_1":
			dialog.text = "邪魔してすまねえ、船長、だが急用なんだ。";
			link.l1 = "ああ、本当に大事な用件だといいがな、アロンソ。報告しろ。";
			link.l1.go = "DTSG_Alonso_2";
		break;
		
		case "DTSG_Alonso_2":
			dialog.text = "イギリスの船が近づいてきてるぜ。あれは……「ミラージュ」だ、船長。";
			link.l1 = "なんだと？本当に確かか？また酒でも飲んでたんじゃねえのか？";
			link.l1.go = "DTSG_Alonso_3";
		break;
		
		case "DTSG_Alonso_3":
			dialog.text = "間違いないぜ、船長――カリブにあんな船は他にねえって、あんたも知ってるだろう。";
			link.l1 = "確かにな。俺が自分で見に行ってやるぜ――この“ミラージュ”とやらが本物かどうか、確かめてやろうじゃねえか。";
			link.l1.go = "DTSG_GotovimsyKBitve";
		break;
		
		case "DTSG_GotovimsyKBitve":
			DialogExit();
			AddQuestRecord("DTSG", "17");
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				sld = characterFromId("Helena");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Saga\Helena.c";
				sld.Dialog.CurrentNode = "Helena_officer";
			}
			if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				sld = characterFromId("Tichingitu");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
			{
				sld = characterFromId("Knippel");
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
				sld.Dialog.CurrentNode = "Knippel_officer";
			}
			
			PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
			PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
			PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";
			
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.Buttons.Save.enable = true;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;
		
		case "DTSG_Kortni":
			dialog.text = "おお…だが、まだ終わっちゃいねえぞ！ブライアン、そこにいたのか！一体どこをほっつき歩いてたんだ！？";
			link.l1 = "これは避けられぬ運命を少し遅らせるだけだ。";
			link.l1.go = "DTSG_Kortni_Pikar";
		break;
		
		case "DTSG_Kortni_Pikar":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
			LAi_SetImmortal(npchar, false);
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
			sld.name = "Brian";
			sld.lastname = "Tasse";
			GiveItem2Character(sld, "blade_20");
			EquipCharacterByItem(sld, "blade_20");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterByItem(sld, "pistol5");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetHP(sld, 300.0, 300.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
			sld.location = "None";
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "DTSG_Kortni_1":
			dialog.text = "シャルル・ド・モール。ここまで来るとはな。惜しいぜ。この船で油断してるお前を捕まえたかったんだがな。";
			link.l1 = "俺が誰だかわかってるのか？じゃあ、最近の騒ぎの黒幕はお前ってわけだな――ぬくぬくした巣から追い出されて、自分で出てくるしかなくなった偉そうな鳥って顔してやがる。 他のハゲタカでも送り込むんじゃなくてな。";
			link.l1.go = "DTSG_Kortni_2";
			
			Island_SetReloadEnableGlobal("Antigua", true);
			bQuestDisableMapEnter = false;
			LAi_LocationDisableOfficersGen("SentJons_town", false);
			DeleteQuestCondition("DTSG_KortniPotopil");
		break;
		
		case "DTSG_Kortni_2":
			dialog.text = "その通り、どちらも正解だ。貴族は遠くからでも同類を見分けられるものだろう。トーマス・リンチ大佐だ。\nどうやら、互いを滅ぼそうとするより紳士らしく話す時が来たようだな。\nお互いに利益のある合意に至れるかもしれん。";
			link.l1 = "何も約束はできんが、少なくとも紳士として言葉は守る。ちゃんと話し合おうじゃないか、大佐。";
			link.l1.go = "DTSG_Kortni_3";
		break;
		
		case "DTSG_Kortni_3":
			dialog.text = "わかったぜ。フリートウッドとはこんな話はできなかったからな。だが、あいつの弱みを握ったし、 もう俺たちにちょっかいは出せねえだろう。お前とうまくいかなかったのは残念だが、まあ仕方ねえさ。";
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				link.l1 = "カリブ中がリチャードの死について噂してるぜ。つまり、お前だったのか！それに、 さっき言ってた切り札ってのはアビゲイルのことか？ところで、あいつはどうなったんだ？\n";
				AddComplexLandExpToScill(50, 50, 50);
				Log_info("Experience bonus received");
			}
			else
			{
				link.l1 = "脅威じゃないって言うのか？…じゃあ、あいつを殺したのか？お前は伯爵の味方なのか？";
			}
			link.l1.go = "DTSG_Kortni_4";
		break;
		
		case "DTSG_Kortni_4":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "アビゲイルか？ああ、あの若いユダヤ娘、あいつの婚約者だな。やっぱり、あんたはなかなか鋭い奴だぜ。 彼女は無事に生きてる――それは約束通りだ。フリートウッドの協力と引き換えにな。";
				link.l1 = "なかなかの協力ぶりだな、言わせてもらうぜ。\nだが、なぜそんなことをしたんだ？伯爵の支持者ってわけか？";
			}
			else
			{
				dialog.text = "支援者？いや、まったく逆だぜ。だがな、時にはあるカードが重荷になって、もう使えなくなることもあるんだ。 残念だが、リチャードもその一枚になっちまったんだよ。";
				link.l1 = "なるほどな。証人は全員消すってわけか。アビゲイルはどうなった？あいつも殺したのか？";
			}
			link.l1.go = "DTSG_Kortni_5";
		break;
		
		case "DTSG_Kortni_5":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "とんでもねえ。まったく逆だぜ。だが、リチャードは知りすぎていたし、 旧世界に戻ったことで危険な存在になっちまった。ここに残ってりゃ、俺たちが命を奪うこともなかったのによ。";
				link.l1 = "「お前は今まで自分の下で働いた奴らを全員始末するのか、大佐？」";
			}
			else
			{
				dialog.text = "誰だって？ああ、あいつの婚約者か。まあ、そうだろうな。彼女が人質だったんだ。あいつの命と引き換えによ。 彼女は無事だ、わしの名誉にかけて誓うぞ。";
				link.l1 = "お前がやったことを考えれば、名誉ってもんが何か分かってるとは思えねえな、大佐。";
			}
			link.l1.go = "DTSG_Kortni_6";
		break;
		
		case "DTSG_Kortni_6":
			if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
			{
				dialog.text = "その挑発には乗らねえぞ、旦那。";
				link.l1 = "じゃあ答えてくれ――どうやってこの船を手に入れたんだ？これは……『ミラージュ』か？";
			}
			else
			{
				dialog.text = "権力を持ったことも、物事の秩序を左右したこともない奴からの侮辱だから、今回は大目に見てやるぜ。";
				link.l1 = "ところで、「ミラージュ」はどこで手に入れたんだ？こいつがその船か？";
			}
			link.l1.go = "DTSG_Kortni_7";
		break;
		
		case "DTSG_Kortni_7":
			dialog.text = "いや、そうでもねえな。立派な船だろう？だが、お前に対してその役目を果たせなかったのは残念だぜ。で、 この船の歴史を知ってるか、ド・モール船長？";
			link.l1 = "「幽霊船とイギリス商人狩りのことか？」";
			link.l1.go = "DTSG_Kortni_8";
		break;
		
		case "DTSG_Kortni_8":
			dialog.text = "あれか？いや、違う。俺が言ってるのは有名な話じゃねえ。人目につかない、隠されたことだ。 このケッチはヨハン・ファン・メルデンとルーカス・ローデンブルクの設計なんだ\nあの二人は色んな策を巡らせて、最終的にハバナの造船所からこの船を進水させたんだ。 運良く俺たちはオリジナルの設計図を手に入れることができた。そして最後には、ミラージュ号を完全に再現し、 設計の欠点を直してさらに改良までしたんだぜ。";
			link.l1 = "残念だが、自分で言った通り、大して役に立たなかったな、大佐。";
			link.l1.go = "DTSG_Kortni_9";
		break;
		
		case "DTSG_Kortni_9":
			dialog.text = "笑ってる気分か？やめとけ。お前が船長としても戦士としても俺を上回ったのは認める。だが、 ここではまだ俺の方が有利だぜ。";
			link.l1 = "それは死に際のはったりか？それとも、お前みたいな連中によくあるただの自信過剰か？その言葉の裏に何があるんだ？";
			link.l1.go = "DTSG_Kortni_10";
		break;
		
		case "DTSG_Kortni_10":
			dialog.text = "素晴らしい質問だな。俺の調査じゃ、お前はただの女たらしで決闘好きの野郎かと思ってたが、それ以上のようだ。 俺はこの会談のすべての結末に備えてきたぜ。たとえお前の剣や弾丸、あるいは流れ弾で俺が死ぬ場合でもな。 もし今日俺が死んだら、お前もチャーリーもフリートウッドに加わらなかったことを後悔するだろうよ。";
			link.l1 = "また賞金稼ぎどもか？勘弁してくれよ。あの時も不愉快で退屈だったが、命の危険はなかったぜ。あの時も追い払ったし、 今回も追い払ってやるさ。";
			link.l1.go = "DTSG_Kortni_11";
		break;
		
		case "DTSG_Kortni_11":
			dialog.text = "疑いはねえよ。今また、あの無鉄砲な決闘者がしゃべってるのが見えるぜ。賞金稼ぎだけじゃねえ。 シーフォックスの連中も、イギリス海軍の諜報部も、漁師の舟に嵐の波がぶつかるみてえに、 お前の頭上に襲いかかってくるぞ。";
			link.l1 = "俺に何の用だ？降伏しろなんて思ってねえだろうな？";
			link.l1.go = "DTSG_Kortni_12";
		break;
		
		case "DTSG_Kortni_12":
			dialog.text = "もちろん違う。これまでの間、あなたのことは十分に調べさせてもらった。\n互いに利益のある取引を提案したい。断るのは賢明じゃない話だ。\nそして、我々は両者とも紳士だ、合意に至れることを願っている。";
			link.l1 = "ではもう一度聞こう、大佐、何の用だ？チャーリーのことか？……それで、俺に何か見返りを用意できるとでも？俺はな、たかが金貨数枚で裏切るような男じゃねえぞ。";
			link.l1.go = "DTSG_Kortni_13";
		break;
		
		case "DTSG_Kortni_13":
			dialog.text = "また正解だな。ただの金貨数枚なんかじゃねえ、言った通り、山ほどの金だ――一万ドゥブロンだぜ。もし話がまとまれば、ポートロイヤルの銀行家に前金が用意されることになってる\nだが一番大事なのは、俺が提案するのはお前の命そのものだ、ド・モール船長。聞こえただろう。 今ここで全員が武器を捨てて、チャーリーを引き渡せば、追跡はすべて止める\n「人間対社会」って言葉を聞いたことがあるか？お前の場合、拒めば「人間対国家」になるんだ。決めろ、チャールズ。 今ここでだ。";
			link.l1 = "肩書きや権力で馬鹿を脅すのは簡単だろうが、俺はそんな馬鹿じゃねえ。\nそれに、必死さは遠くからでも嗅ぎ取れるんだ。\n出て行け。\n俺がお前を殺さなかったことを感謝しろ――それだけの価値はあるんだからな。";
			link.l1.go = "DTSG_Kortni_PkCh_1";
			link.l2 = "チャーリーが本当に必要なんじゃねえだろ、大佐。必要なのはあいつの沈黙だ。";
			link.l2.go = "DTSG_Kortni_LT_1";
			link.l3 = "俺がこれを承諾するのは、自分と部下たちの安全のためだ。あんたの金が欲しいわけじゃねえ、そこは勘違いすんなよ。";
			link.l3.go = "DTSG_Kortni_Sdat";
		break;
		
		case "DTSG_Kortni_PkCh_1":
			dialog.text = "人生で最悪の決断の一つをしたな、ド・モール船長。俺はお前を羨ましくもなんともねえよ。本当にそうだ。 自業自得だぜ――もう二度とこんな申し出は誰からも受けられねえ。特に俺からはな。じゃあな。";
			link.l1 = "「待て、カーネル。」";
			link.l1.go = "DTSG_Kortni_PkCh_2";
		break;
		
		case "DTSG_Kortni_PkCh_2":
			dialog.text = "なんだ、気が変わったのか？俺の言葉がやっと効いたってわけか？";
			link.l1 = "ああ、まったく逆だ。";
			link.l1.go = "DTSG_Kortni_PkCh_3";
		break;
		
		case "DTSG_Kortni_PkCh_3":
			dialog.text = "どういう意味だ？説明しろ。";
			link.l1 = "お前の言葉で、ますますお前に立ち向かう決意が固まったぜ。\nそんな顔するな――殺しはしねえよ。言っただろ、逃がしてやるってな。\nだが、船なしでも何とかなるだろうさ。";
			link.l1.go = "DTSG_Kortni_PkCh_4";
		break;
		
		case "DTSG_Kortni_PkCh_4":
			dialog.text = "俺にはいらねえ、船があるからな。";
			link.l1 = "あんたの言う通りだ。だが、必要ないってことだけはな。あんたは影響力のある男かもしれねえが、 分別も気配りも足りねえ。俺はあんたがいつもやってることをやるさ――状況を支配する側になるってことだ。";
			link.l1.go = "DTSG_Kortni_PkCh_5";
		break;
		
		case "DTSG_Kortni_PkCh_5":
			dialog.text = "お前は違うぞ、ド・モール船長。自分をごまかすな。";
			link.l1 = "完全にか？まあ、そうじゃねえな。でもあんたも同じだぜ――今やあんたの命は俺の手の中だ、カーネル。\nこの先俺がどうなろうと関係ねえ――今は好きにできる。だから俺は……この船をもらうぜ。\nあんたは自由だ。岸はすぐそこだ。";
			link.l1.go = "DTSG_Kortni_PkCh_6";
		break;
		
		case "DTSG_Kortni_PkCh_6":
			dialog.text = "お前にはそんな度胸はねえだろう。\nだが、その顔つきからすると……まあ、ちっぽけな勝利を楽しむんだな。\nお前はやっちまったな……";
			link.l1 = "ああ、ああ、人生で最悪の決断の一つだったよ。もう何度も聞いたさ。さあ、この船から降りろ。俺の船だ。 自分で飛び込むか、それとも俺たちが海に放り込んでやろうか？";
			link.l1.go = "DTSG_Kortni_PkCh_7";
		break;
		
		case "DTSG_Kortni_PkCh_7":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_7");
		break;
		
		case "DTSG_Kortni_PkCh_8":
			dialog.text = "まさかあいつがこんな姿になるとは思わなかったぜ――屈辱にまみれ、窓から飛び出して、四つん這いで岸まで泳ぐなんてな。";
			link.l1 = "見えたか？満足したか？結構だ。次はお前の番だぜ。";
			link.l1.go = "DTSG_Kortni_PkCh_9";
		break;
		
		case "DTSG_Kortni_PkCh_9":
			dialog.text = "何を言ってるんだ、旦那？俺たちは敵じゃねえ、命令に従っただけだ！…せめてボートを頼めねえか？もう二度と俺の顔は見ねえよ！";
			link.l1 = "お前が俺の立場で、俺に戦いで負けたなら、俺を見逃したりしねえだろう？だから、殺されなかっただけありがたく思え。 \n窓から出ろ。今すぐだ。\nもしかしたら、お前の後ろ盾に追いつけるかもな。";
			link.l1.go = "DTSG_Kortni_PkCh_10";
		break;
		
		case "DTSG_Kortni_PkCh_10":
			dialog.text = "こんな屈辱を味わうくらいなら死んだほうがマシだ、旦那！";
			link.l1 = "お望みどおりに。";
			link.l1.go = "DTSG_Kortni_PkCh_11";
		break;
		
		case "DTSG_Kortni_PkCh_11":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;
		
		case "DTSG_Kortni_PkCh_12":
			dialog.text = "「あれが大佐だったんだろう、船長？」";
			link.l1 = "そうだ。窓の外を見てみろ、チャーリー、後悔はしねえぞ。";
			link.l1.go = "DTSG_Kortni_PkCh_13";
		break;
		
		case "DTSG_Kortni_PkCh_13":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_PkCh_13");
		break;
		
		case "DTSG_Kortni_PkCh_14":
			dialog.text = "大佐が……？こんなことを見る日が来るとは思わなかったぜ、旦那。あんな肩書きを持つ男を、 ただの水夫みたいに海に放り投げるなんて、よくもまあやるもんだ！リチャードなら絶対にそんなことはしねえ――階級を尊重するのがあいつの信条だったからな。";
			link.l1 = "何年もの訓練で叩き込まれたんだ。あいつは軍人で、その考え方も軍人そのものだ。\n俺は違う。もっと広い視野で考えるし、そんな…制約には縛られちゃいない。";
			link.l1.go = "DTSG_Kortni_PkCh_15";
		break;
		
		case "DTSG_Kortni_PkCh_15":
			dialog.text = "「こんなことをしても、俺たちが咎められることはねえのか？」";
			link.l1 = "へっ、リチャードを責めてるくせに、考え方はあいつと同じじゃねえか。俺たちは逆らったから、 しばらくは追われるだろうよ。だが、遅かれ早かれ、イギリス海軍だって俺たちを諦めるさ。リンチにとっちゃ、 これからは私怨になるだろうがな。だが、次はあいつの背後に国の力がつかないようにしてやったぜ。";
			link.l1.go = "DTSG_Kortni_PkCh_16";
		break;
		
		case "DTSG_Kortni_PkCh_16":
			dialog.text = "なあ、船長、今日からお前さんのことをもっと尊敬するぜ。ディックと一緒にヴァルキリー号で出ていかず、 お前さんについてきたことを、俺は絶対に後悔しねえよ。";
			link.l1 = "ありがとう、相棒！覚悟しとけよ――嵐が近づいてきてるんだ。でもな、なんとなくまた俺たちが勝つ気がするぜ。さあ、行こう、甲板に戻る時間だ。";
			link.l1.go = "DTSG_Kortni_PkCh_17";
		break;
		
		case "DTSG_Kortni_PkCh_17":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			
			DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
			Achievment_Set("ach_CL_114");
		break;
		
		case "DTSG_Kortni_LT_1":
			dialog.text = "それは完全に正しくはないが、個人的にはチャーリーがこれから黙っていてくれるならどうでもいい。だが、 俺の仲間たちはあいつの死体を見たがっているんだ。それに、やつらはチャーリーの顔を知ってる\nこれは現実の人生だ、チャールズ。子供の頃に乳母が読んでくれたおとぎ話や騎士の詩じゃねえ。 みんなが満足する解決策なんて、俺には見えないぜ。";
			link.l1 = "だが、俺はやるぜ。似たような死体なんていくらでも見つかるし、服だって同じようなものを買えばいい。 ちょっと袖の下を使えば済む話だ。それに、チャーリーとも話をつけておく。俺の言葉を保証にするぜ。";
			link.l1.go = "DTSG_Kortni_LT_2";
		break;
		
		case "DTSG_Kortni_LT_2":
			if (sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				dialog.text = "……大きな危険だぜ。俺があんたの言葉を信じられるかどうかだけの問題じゃねえ。 仲間たちがチャーリーそっくりの死体を見たとき、俺の話を信じてくれるかどうかも関わってくるんだ。だから、 その危険を……そう簡単には冒さねえよ。";
				link.l1 = "いくらだ？";
				link.l1.go = "DTSG_Kortni_LT_4";
			}
			else
			{
				Notification_Reputation(false, 71, "low");
				dialog.text = "お前みたいな評判の男の言葉なんざ、冗談だろう？\n貴族の生まれだけじゃ信用にはならねえよ。";
				link.l1 = "同じような生まれや行いを持つ男からこれを聞かされて……すまねえな、大佐。";
				link.l1.go = "DTSG_Kortni_LT_3";
			}
		break;
		
		case "DTSG_Kortni_LT_3":
			dialog.text = "もちろん、その通りだ。だが今回は、他の誰でもなく、俺の信頼の問題だ。そして保証人としてお前じゃ納得できねえ\n最後にもう一度言う。チャーリーを渡せ。もちろん、フリートウッドと同じ運命を辿りたくないならな。";
			link.l1 = "肩書きや権力で馬鹿を脅すのは簡単だろうが、俺はそんな馬鹿じゃねえ。\nそれに、必死さなんざ遠くからでも嗅ぎ取れるんだ。\n出て行け。\n俺がお前を殺さなかっただけでもありがたく思え――そのくらいの報いは受けて当然だぜ。";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_4":
			dialog.text = "やっと核心に入ったな。百万ペソだ。これが最後の提案だぜ。";
			if (sti(pchar.Money) >= 1000000)
			{
				link.l1 = "金は払うぜ。俺が貧乏だとか、部下の命を軽く見てるなんて思うなよ。どっちも違うんだ。受け取れ。";
				link.l1.go = "DTSG_Kortni_LT_7";
			}
			else
			{
				link.l1 = " 食欲はあるな、まあそれくらいは予想してたが。だが今はそんなに持ってねえんだ、それに……";
				link.l1.go = "DTSG_Kortni_LT_5";
			}
		break;
		
		case "DTSG_Kortni_LT_5":
			dialog.text = "銀がなきゃ、取引はなしだ。俺が情けをかけると思ったのか？俺が聖人に見えるか、旦那？";
			link.l1 = "でも、もう少し待ってくれないか？どこで、いつならまた会うのに都合がいい？ 金貸しからドブロン金貨を借りることもできるんだ。";
			link.l1.go = "DTSG_Kortni_LT_6";
		break;
		
		case "DTSG_Kortni_LT_6":
			dialog.text = "じゃあ、あんたは俺が思ってた以上に俺のことを世間知らずだと思ってるんだな\n俺は田舎娘じゃねえ、昔一度手を出された相手をいつまでも待つような女じゃない\n金がない？最初からそんなもん頼んじゃいねえ。俺が欲しいのはチャーリーだけだ。あんたなんか、 いくら迷惑かけられても俺には何の役にも立たねえよ。";
			link.l1 = "肩書きや権力で馬鹿を脅すのは簡単だろうが、俺はそんな馬鹿じゃねえ。必死さなんて遠くからでも嗅ぎ取れるんだ。 出ていけ。俺が殺さなかっただけありがたく思え――お前にはそれだけの価値があるんだからな。";
			link.l1.go = "DTSG_Kortni_PkCh_1";
		break;
		
		case "DTSG_Kortni_LT_7":
			dialog.text = "そんなに哀れなチャーリーに執着してるのか？まあ、あんたの高潔さは認めてやるよ。だが、 砲手には墓場みたいに口を閉ざさせておけ。\nさもないと、二人とも墓場行きだぜ。";
			link.l1 = "約束するぜ。だからお前も約束を守って、追跡は全部やめろよ。";
			link.l1.go = "DTSG_Kortni_LT_8";
			AddMoneyToCharacter(pchar, -1000000);
		break;
		
		case "DTSG_Kortni_LT_8":
			dialog.text = "俺も約束するぜ。それと、もう一つ。\nお前が正々堂々と勝ったのは認めるが、俺の船は持っていかせてもらう。\nあれは特注品なんだ。しかも、すげえ高かったんだぜ。";
			link.l1 = "勝者の権利はどうなるんだ？だが、今回は運を試すのはやめておくぜ。";
			link.l1.go = "DTSG_Kortni_LT_9";
		break;
		
		case "DTSG_Kortni_LT_9":
			DialogExit();
			
			LAi_FadeLong("DTSG_Kortni_Otkup_1", "");
		break;
		
		case "DTSG_Kortni_LT_10":
			dialog.text = "悪いが、ブライアン、こう言うのは心苦しいが、俺たちの協力関係はここまでだ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_11";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_11":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_12";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_12":
			dialog.text = "俺は……自由になったのか、カーネル？俺の首にかかった賞金を取り下げてくれるのか？そうすりゃ、 まるで俺が法を守る人間みたいに新しくやり直せるってのか？";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_13";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_13":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_14":
			dialog.text = "お前は見すぎたな――まるで故フリートウッドみたいにさ。今、俺はお前の目の前で賄賂を受け取ったも同然だぜ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_15";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_15":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_16":
			dialog.text = "お、俺は……誰にも何も言わねえ、神に誓って！";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_17";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_17":
			DialogExit();
			sld = CharacterFromID("DTSG_KortniClone");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_18":
			dialog.text = "もちろん、しないだろうよ。";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_19";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_Mrt_Rocur"));
		break;
		case "DTSG_Kortni_LT_19":
			DialogExit();
			sld = CharacterFromID("DTSG_Mrt_Rocur");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_LT_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "DTSG_Kortni_LT_20":
			dialog.text = "「いやっ……」";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_LT_21";
			CharacterTurnByChr(npchar, CharacterFromID("DTSG_KortniClone"));
		break;
		case "DTSG_Kortni_LT_21":
			DialogExit();
			
			sld = CharacterFromID("DTSG_KortniClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "1", 1.8);
			DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);
			
			LAi_SetActorType(NPChar);
			LAi_ActorAttack(NPChar, sld, "");
		break;
		
		case "DTSG_Kortni_LT_22":
			dialog.text = "そんな目で見るなよ、チャールズ。ブライアンが口を滑らせやしないかって毎日気にしてたら、俺は一睡もできねえぞ。";
			link.l1 = "俺が今見たことに驚くべきかどうか、もう自分でもわからねえぜ。";
			link.l1.go = "DTSG_Kortni_LT_23";
		break;
		
		case "DTSG_Kortni_LT_23":
			dialog.text = "そうするべきじゃねえ。わしはもう腹を決めたんじゃ。お前たち二人に求めるのは、起きたことを黙っていることだけだ。 \n似たような死体を探して、顔をうまく細工して、金を有効に使い、仲間たちをうまく説得してみせるさ。";
			link.l1 = "ありがとうございます、大佐。";
			link.l1.go = "DTSG_Kortni_LT_24";
		break;
		
		case "DTSG_Kortni_LT_24":
			dialog.text = "まだ礼を言われるようなことはしてねえさ。俺の話を信じてもらえねえ危険は常にあるし、 そうなりゃまた追われる羽目になる。\n今はこれで失礼するぜ、ド・モール船長。俺は自分の船で出航する。異論はねえだろう――お前とチャーリーにはもう十分な恩を売ったからな。";
			link.l1 = "じゃあ、さらばだな。";
			link.l1.go = "DTSG_Kortni_LT_25";
			
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;
		
		case "DTSG_Kortni_LT_25":
			DialogExit();
			AddDialogExitQuestFunction("DTSG_Kortni_LT_25");
		break;
		
		case "DTSG_Kortni_LT_26":
			dialog.text = "お前は今誰と話してたかわかってるのか、船長？大佐だぞ！あいつがこの騒ぎを仕組んだ張本人なのか？";
			link.l1 = "知ってるさ、あいつは自己紹介してたぜ。お前の言う通り――そうだったよ。";
			link.l1.go = "DTSG_Kortni_LT_27";
		break;
		
		case "DTSG_Kortni_LT_27":
			dialog.text = "妙だな、旦那。俺はかつてあいつをリチャードの上官として知ってたんだぜ。どうしてそんなことがありえるんだ？ それに、まるで何もなかったみてえに立ち去るのはなぜだ？そもそも、あいつは何の用だったんだ？\n";
			link.l1 = "実のところ、何もおかしなことじゃねえ。裏の命令を実行する奴らは、 敵よりもむしろ上の連中のせいで命を危険にさらすもんだ。あいつはお前の首を狙ってたんだぜ、チャーリー。";
			link.l1.go = "DTSG_Kortni_LT_28";
		break;
		
		case "DTSG_Kortni_LT_28":
			dialog.text = "わしにはわからんぞ、船長。じゃが、なぜあいつは去るんじゃ？負けを認めたのか？";
			link.l1 = "あいつらしくもねえな。お前の頭ぐらいの重さの金を渡さなきゃならなかったんだぜ。いや、 それよりちょっと多かったかもな。正確には百万ペソだ。";
			link.l1.go = "DTSG_Kortni_LT_29";
		break;
		
		case "DTSG_Kortni_LT_29":
			dialog.text = "お前…あんな大金を払ったのか？俺のために…？";
			link.l1 = "ああ、別にお前だけのためじゃねえさ。俺自身のためでもあるし、みんなのためでもある。だがな、チャーリー、 やっぱり一番はお前のためだ。もしあいつを殺してたら、その後ずっと報復の遠征隊に追われる羽目になってただろうよ。 ";
			link.l1.go = "DTSG_Kortni_LT_30";
		break;
		
		case "DTSG_Kortni_LT_30":
			dialog.text = "俺は…信じられねえよ、旦那。とにかく…ありがとう。フリートウッドがあんたの立場でそんなことをするとは思わなかったぜ。";
			link.l1 = "あいつが逃げた後で、あんたは奴に対して偏見が強すぎるぜ。 リチャードはただアビゲイルと静かで平和な暮らしを望んでいただけだ。うまくいかなかったのは気の毒だがな。しかも、 ちゃんと約束を守ってあんたの借金も返してくれたじゃねえか。へっ、俺もフリートウッドも――チャーリー、お前は本当に船長運がいいよな、なあ？\n";
			link.l1.go = "DTSG_Kortni_LT_31";
		break;
		
		case "DTSG_Kortni_LT_31":
			dialog.text = "冗談じゃねえぞ、船長。で、これで全部終わったのか？";
			link.l1 = "ああ、高くつく友よ。少なくとも今のところはな。戦いは終わった――野郎どもに武器をしまうよう伝えてくれ。\nそれから帆を揚げる準備をさせておけ。";
			link.l1.go = "DTSG_Kortni_LT_32";
		break;
		
		case "DTSG_Kortni_LT_32":
			DialogExit();
			
			InterfaceStates.Buttons.Save.enable = true;
			LAi_SetPlayerType(pchar);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			npchar.Dialog.CurrentNode = "Knippel_officer";
			npchar.location = "None";
			
			AddQuestRecord("DTSG", "19");
			CloseQuestHeader("DTSG");
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
			sld = CharacterFromID("Knippel");
			SetCharacterPerk(sld, "Bombardier");
			notification("Bombardier Unlocked", "Knippel");
		break;
		
		case "DTSG_Kortni_Sdat":
			dialog.text = "お前が同意する理由なんざ、欲だろうが、恐れだろうが、部下への義務だろうが、俺にはどうでもいい。\n肝心なのは、お前が同意したってことだ。\n俺の部下をポートロイヤルに送って、銀行家への指示を伝えさせるぜ。";
			link.l1 = "よし。やっとこれで終わったなんて信じられねえな。";
			link.l1.go = "DTSG_Kortni_Dengi_1";
			link.l2 = "なあ、金なんてくそくらえだ。金ならいくらでもまた手に入るさ。チャーリーのことで、 他にお前に求めたいものがあるんだ、カーネル。";
			link.l2.go = "DTSG_Kortni_Kech_1";
		break;
		
		case "DTSG_Kortni_Kech_1":
			dialog.text = "おお？正直言って驚いたぜ、ド・モール船長。で、お前さんの考えじゃ、もし山ほどの金が気に入らねえなら、 老砲手のこの禿げ頭に匹敵するもんは何だってんだ？";
			link.l1 = "自分で言ったじゃねえか――見事な船だ、設計の欠陥も直されてる。俺自身で試してみたくてうずうずしてるんだ。設計図はまだ持ってるだろう？ でもチャーリーは一人しかいねえ。それに、俺を満足させておくのはお前のためでもあるぜ。";
			link.l1.go = "DTSG_Kortni_Kech_2";
		break;
		
		case "DTSG_Kortni_Kech_2":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				Notification_Reputation(true, 71, "low");
				Notification_Perk(true, "Trustworthy");
				dialog.text = "交渉が手強いな。これ一つ作るのにどれだけ金がかかったかわかってるのか？";
				link.l1 = "（信頼）（名誉）よくわかってるさ、だからこそ聞いてるんだ。お前の手は肘まで俺の顎の中だぜ。 この狼を撃とうってのもいいが――手を失うことになるぞ。それだけじゃ済まねえ。";
			}
			else
			{
				dialog.text = "これを一隻造るには、用意した金貨よりずっとかかるんだ、残念ながらな。\nだが、お前には楽しませてもらったぜ、チャールズ。いい意味でな。";
				link.l1 = "やってみる価値はあったな。";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
			}
			link.l1.go = "DTSG_Kortni_Kech_3";
		break;
		
		case "DTSG_Kortni_Kech_3":
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				dialog.text = "自分の望みがはっきりしていて、人生の目標に向かって突き進んでるんだな\nよし、わかった。そのケッチはお前のもんだ。ただし、金のことは忘れろ――金貸しは何も知らねえって言うだろうよ。";
				link.l1 = "それで構わねえ。";
				link.l1.go = "DTSG_Kortni_Kech_4";
				pchar.questTemp.DTSG_Kech = true;
			}
			else
			{
				dialog.text = "間違いねえ。俺の人生は、チャンスをつかみ、危険から身を守る物語だったんだ\nだからチャーリーをここに連れてこい、そうすりゃ穏やかに別れようじゃねえか。 その後なら保証金も持っていっていいさ。でも、この船で俺は出ていくぜ。";
				link.l1 = "じゃあ、決着をつけようぜ。";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
				pchar.questTemp.DTSG_depozit = true;
			}
		break;
		
		case "DTSG_Kortni_Kech_4":
			dialog.text = "満足してるとは言えねえが、早く終わらせたいんだ。さあ、俺の欲しいものを渡せ。";
			link.l1 = "「何」じゃなくて「誰」だ。でも、好きにしな。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;
		
		case "DTSG_Kortni_Dengi_1":
			dialog.text = "俺にも分からねえよ。最近思うんだが、人間が何者かってだけじゃなく、誰と一緒にいるかってのも大事なんじゃねえか――年寄りの砲手を捕まえるだけの簡単な仕事が、そいつの船長、つまりお前だよ、チャールズ、 のおかげで頭痛の種になっちまったんだ\nチャーリーをここに呼べ。このゴタゴタもこれで終わりだ――錨を上げて、それぞれの船が別の道を行くぜ。";
			link.l1 = "「別れる、だと？」";
			link.l1.go = "DTSG_Kortni_Dengi_2";
		break;
		
		case "DTSG_Kortni_Dengi_2":
			dialog.text = "驚いたか？ケッチが自分の正当な戦利品だと思ってたんじゃねえのか？俺たちは海賊じゃねえぞ、ド・モール船長。 文明人はもっと複雑なルールで生きてるんだ。船は俺が預かるぜ。";
			link.l1 = "「さて……」";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel":
			DialogExit();
			
			//sld = CharacterFromID("Knippel");
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
			sld.id = "KnippelClone";
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_2":
			dialog.text = "大丈夫か、旦那？あれは…大佐か？";
			link.l1 = "ああ、チャーリー、わしだ、隊長じゃ。ちょうどいい時に来てくれたな――今まさにお前を迎えに行こうとしていたところだったんじゃ。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_3":
			dialog.text = "俺を呼んだのか、船長？…今すぐか？なんでこんなに長くこの…男と話してたんだ？てっきり何かあったのかと思って、わしが自分で来たんじゃ。";
			link.l1 = "その通りだ。勝ったとはいえ、まだ厄介な状況だぜ。もし俺と大佐が解決策を見つけてなかったら、 今も困ったままだっただろうな。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_4":
			dialog.text = "「奴に俺たちに構うなと説得できたのか、旦那？」";
			link.l1 = "残念ながら、俺だけだ。俺たちじゃねえ。お前は……あいつと行くんだ、チャーリー。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_5":
			dialog.text = "何だと…？でも、なぜだ…？俺たちが勝ったじゃねえか！";
			link.l1 = "わからねえのか？俺たちがずっと勝ち続けられるわけじゃねえ――あいつらはお前の首を取るまで止まらねえんだ。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_6":
			dialog.text = "こんな仕打ちを俺にするなんて信じられねえよ、船長。お前もディックと同じじゃねえか。 二人とも昔は俺の友達だって言ってたくせによ。結局、どっちも俺や身近な奴らを見捨てやがったんだ。";
			link.l1 = "それが船長の重荷であり、責任ってやつだ。お前にはわからねえだろうな、 どうせ大砲に砲弾を詰め込むだけの仕事しかしてこなかったんだからよ。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_7":
			dialog.text = "わからねえのか？…もしかして、俺はお前みたいな裏切り者じゃねえからか？自分がどこへ行くべきかわかってるのか？";
			link.l1 = "地獄へ？あんたの言う通りかもしれねえな。俺たちみんな、その報いを受けるべきだ。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_8":
			dialog.text = "くたばれ、旦那。";
			link.l1 = "...";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_9":
			DialogExit();
			
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			
			sld = CharacterFromID("KnippelClone");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Knippel");
			RemovePassenger(pchar, sld);
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_10":
			dialog.text = "おかしいな。もう少しで笑っちまうところだったぜ。ブライアン、聞いたか？\nたまには、ただの百姓どもの話を聞くのも、そよ風みてえで全然イラつかねえもんだな。チャールズ、 お前は正しい決断をしたんだ。どれだけ辛かったか、わしにも分かる。だが安心しろ、お前も部下も、 もう誰も苦しむことはねえさ。";
			link.l1 = "この約束を守ってくれるといいんだがな、大佐。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_11":
			dialog.text = "俺は約束を守る男だぜ。アビゲイルの運命がその証拠だ。ブライアンも見てみろ。フランスの海賊だが、 肝心な時に正しい側についたんだ。そして、あいつが忠実に仕えている限り、誰も手出しはしねえ。あんたも同じように、 正しい道を進んでるぜ、ド・モール船長。";
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				link.l1 = "移動の話だが、俺はできるだけ早くここを出たいんだ。あんたが約束してくれた、間違いなく速いこの船でな、カーネル。 ";
			}
			else
			{
				link.l1 = "俺は海賊じゃねえ。まだイギリス艦隊に加わるつもりもねえさ。だが、約束された報酬はしっかりいただくつもりだぜ。";
			}
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_12":
			if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
			{
				dialog.text = "隠しはしねえ――まるで心からあいつを引き剥がすような気分だ。新しいのに金を使わなきゃならねえが、それだけの価値はあるかもな。 チャーリーが口を滑らせやしねえかと、ずっと気が休まらなかったからな\nお前が黙っていて、イングランドに対して大きな罪を犯さねえ限り、もう俺たちは敵じゃねえと思ってくれていい。 新しい船を楽しめよ――確かに美しい船だ。さらばだ、チャールズ。ブライアン、俺たちのためにボートを用意しろ。チャーリー――お前に選択肢はねえ、ついて来い。";
				link.l1 = "じゃあな。みんな。";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
			}
			else
			{
				dialog.text = "残念だが、腕の立つ奴は国籍なんざ関係なくいつだって必要だぜ。だがもちろん、報酬はちゃんと受け取る資格がある。 安心してポートロイヤルへ行きな、俺のこのケッチなら他のどの船よりも先に着いてやるさ。";
				link.l1 = "そうだといいがな。それに、ポートロイヤルで武装した護衛が俺を待ち構えてたりしなきゃいいんだが。";
				link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
			}
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_13":
			DialogExit();
			
			AddQuestRecord("DTSG", "20");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_14":
			dialog.text = "また俺の言葉を疑うのか？恥を知れ。お前はイギリス海軍全体の感謝を受けるに値する男だ。何か必要な時や、 俺たちに加わる気になったら、いつでも連絡してくれ、ド・モール船長。";
			link.l1 = "かつて、俺はイギリスの諜報部と繋がりや支援を得ようとしたことがあるんだ。うまくいかなかったがな。\nじゃあな、大佐。";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;
		
		case "DTSG_Kortni_VizyvaemKnippel_15":
			DialogExit();
			
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				ChangeCharacterNationReputation(pchar, ENGLAND, 30);
			}
			pchar.GenQuest.CannotTakeShip = true;
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
			PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
			AddQuestRecord("DTSG", "21");
			CloseQuestHeader("DTSG");
			ChangeOfficersLoyality("bad_all", 5);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "fame", -10);
			AddCrewMorale(Pchar, -10);
			LAi_ReloadBoarding();
			Achievment_Set("ach_CL_114");
		break;
		
	}
} 
