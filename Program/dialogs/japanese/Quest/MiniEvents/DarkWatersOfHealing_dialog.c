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
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;
		
		case "dwh_gypsy_0":
			dialog.text = "...";
			link.l1 = "聞けよ、黒い眉のやつ、お前は重い病気さえも治すって聞いたぜ。本当か？";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "「真実」 "+GetSexPhrase("「あなた」","美しさ")+"。俺にはどんな病も治す自分なりの方法があるんだ。これまで庶民も商人も、裕福な連中さえ立ち直らせてきたぜ。 そうさ、誰も助けられなかったときは総督でさえ俺の薬に頼ったもんだ。病は金を恐れねえが、俺の薬には敵わねえのさ。 ";
			link.l1 = "「それなら、なぜ重病の少女、トーマス・モリソンの娘を治療するのを拒むんだ？」";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "「誰がそんな馬鹿げたことを言ったんだ、」 "+GetSexPhrase("ファルコネット","ラブラブ")+"？俺は助けるのを断ったわけじゃねえ。あの娘の親父が俺を家から追い出したんだ。治療することで合意してたのに、 急に気が変わりやがってよ。まるで仇敵みてえに俺を放り出しやがったんだ。";
			link.l1 = "それでは、彼は自分の手で娘を苦しませることにしたのか？";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "いやいや、あの人は思いやりのある父親だよ。どうしてあんなふうに振る舞ったのか想像もつかないな。";
			link.l1 = "もう一度彼に話しかけてみたか？";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "家に近づくことさえ許してくれないんだ。聞いてくれ、 "+GetSexPhrase("「あなた」","美しさ")+"、あなたが哀れな娘の運命を気にかけてくれるなら、何が起きているのか調べてくれませんか？\nトーマスに話をして、この子が苦しむのを助けてください。";
			link.l1 = "もちろん手伝うぜ。トーマスはどこにいるんだ？";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "いや、黒い眉毛のあんた。どんな事情があろうと、彼女の父親があんたの助けを断るにはそれなりの理由があるはずだ。 俺は口を出さねえ。決めるのはあの男だ――娘なんだからな。";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "奴らの家は町の北側、壁沿いにあって、柱のある大きな屋敷の隣だ。続けてくれ、 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"「彼と話してから私のところに戻ってきてくれ。」";
			link.l1 = "すぐ戻るぜ。";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_5");
		break;

		case "dwh_gypsy_repeat":
			dialog.text = "「さて、」 "+GetSexPhrase("「あなた」","恋人")+"、トマスと話したか？";
			link.l1 = "「まだだ。」";
			link.l1.go = "dwh_exit";
		break;

		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"！何の用で俺の家に来たんだ？";
			link.l1 = "私の名は船長だ "+GetFullName(pchar)+"。ジプシー女の頼みで来たんだ。なぜ彼女の助けを断ったのか知りたがっている。どんなに小さな望みでも、 娘さんを救う機会を本当に拒める立場なのか？";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "ああ、船長……どうかご理解ください、私の意思ではなく、仕方なく断らざるを得なかったのです。信じてください、 エスターが回復するためなら何でも差し出します。";
			link.l1 = "「なぜ、そんなに必死に必要としている助けを拒んだんだ？」";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "ご覧の通り、我が家は昔から信仰深い家系なんだ。妻のオリヴィアが亡くなってからは、信仰だけを頼りに生きてきた。 ジプシーが助けを申し出てくれたとき、私は同意した――娘を救うためなら何でもしたかったんだ。だが……神父にそのことが知られてしまった。";
			link.l1 = "俺の勘だが、あいつはそういうサービスに反対してるんだろう？";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "まさにその通りだ。彼は、祈りと主の御心だけが私の娘を癒せると私に納得させたんだ。もしこの道から外れて“魔女”の助けなんかを借りたら、教会から破門にすると脅されたんだぞ。\nわかるか？破門だ！";
			link.l1 = "つまり、エスターの健康は神父の言葉だけにかかっているのか？";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "私と娘は教会のそばに住んでいます。信仰こそが私たちのすべてです。もしジプシーが失敗したら、私は娘だけでなく、 この世での居場所も失ってしまいます。人々は私たちから離れ、教会も私たちを拒絶するでしょう。 エスターと私は完全に孤立してしまいます。";
			link.l1 = "「もし神父が同意したらどうする？そのときはジプシーに試させるのか？」";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "ああ。もし教会が彼女の行いを祝福したのなら……俺は彼女を信じるぜ。役に立つことなら何でもやってみる覚悟だ。";
			link.l1 = "なるほど。よし、トーマス、手を貸してやろう。君の神父と話してみる。もしかしたら説得できるかもしれないな。";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "お前…本当に俺たちを助けてくれるのか？船長、あなたの成功を祈っているぜ。だが覚えておいてくれ…うちの神父は頑固で信念の強い男だ、説得するのは簡単じゃねえぞ。";
			link.l1 = "信念も説得力のある議論で乗り越えられるさ。\n待っててくれ、すぐ戻るぜ。";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_7");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "トマス、神父を説得することに成功した。";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "本当か？信じられねえ！じゃあ、できるだけ早くジプシーを招こうぜ。";
			link.l1 = "もちろんそうしますが、一つだけ問題があります。神父は、これがあなたの信仰を揺るがすことなく、 心からの悔い改めと善行を期待しています。その善行の一つとして、 教区のために新しい鐘を購入することが挙げられます。";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "ああ、船長……鐘はかなりの金がかかるんだ。亡き妻の宝石のいくつかを手放さなきゃならんかもしれん。でもエスターのためなら、 持っているものすべて、それ以上でも惜しくはない。もちろん、主に許しを請うつもりだ。鍛冶屋に行って注文を出し、 ジプシーも探すよ。\n神父には、鐘がもうすぐ用意できると伝えてくれ。たとえ地の底からでも、必ず手に入れてみせる。";
			link.l1 = "「よろしい、Thomas。」";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_14");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "お前が言ったことは神父に伝えたぜ。もうお前の邪魔はしねえから、始めていいぞ。";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "ご協力ありがとうございます、船長！どうぞ、この五十ドゥブロンをお受け取りください。 今の私にできることはこれくらいしかありませんが……";
			link.l1 = "馬鹿を言うな！俺は金のために手を貸したんじゃねえ。さてと……治療の準備は全部できてるんだな？";
			link.l1.go = "Tomas_16_1";
			link.l2 = "そうかい、そこまで言うなら……他に俺にできることはあるか？";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "娘の健康を取り戻すための薬を作るには、マンガローザという珍しい植物が必要だ。 人の手がほとんど入らない場所に生えるんだ。町の外に洞窟があってな、そこにはよく…ろくでなしどもがたむろしている。あいつらはマンガローザを煙草代わりに燃やして吸ってやがるが、 その力には気づいていない。頼む、手を貸してくれ。\n "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"「マンガローザを取ってきてくれ、あれがないと何も始まらねえ。」";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "マンガローザか？その植物なら知ってるぜ。";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "どんなふうに見えるんだ？";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "それはかなり背の高い植物で、葉が裂けていて、心地よく酔わせるような香りがする。 他のものと間違えることはないだろう。";
			link.l1 = "よし、そのマンガローザを探してくるぜ。";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "お前もそれをタバコに混ぜて吸うのか？";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "いや、全然違うぜ！アメリアっていう治療師がいるんだ。あいつはそれを使って、 まさに頭がひっくり返るような薬を作るんだよ。";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "いや、でもマンガローザは何度か扱ったことがあるぜ。";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "アメリアを知っているのか？そうか、\n "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"そのうち、俺に本気で勝負を挑んでくるようになるだろうな。\nだが、今はそんな時じゃねえ。マンガローサを取ってきてくれ、俺は全部準備しておくぜ。";
			link.l1 = "向かうぞ。";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "なるほど、あんたはただ者じゃねえな。 "+GetSexPhrase("ファルコネット","ラブラブ")+"。あなたの知識は広大で、頭脳は刃のように鋭い！未知の世界にも恐れず踏み込み、 他の者が避けるものさえも進んで手に入れようとする。その助けを得られるトーマスは幸運だ。さあ、行ってくれ、 マンガローザを持ってきてくれれば、あの娘を癒してやろう。";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_22");
		break;
		
		case "Bandit_1":
			dialog.text = "ははは。言ってるだろ、マーク、あいつは間抜けだ。家に鍵すらかけてねえんだぜ。";
			link.l1 = "「本当にあいつの雌鶏は家でじっとしてるんじゃねえのか？」";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_2");
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "ほうほう、新鮮な魚が俺たちの網にかかったぜ！さあ、突っ立ってないで、さっさとポケットの中身を出せ。 機嫌が悪くなる前にな。";
			link.l1 = "落ち着けよ、野郎ども。俺は仕事で来たんだ。 "+sld.name+" 俺を寄越したんだ。マンガロサが必要だ。";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "「君が言う」 "+sld.name+" 「お前が使いか？よし、マンガローザはあるぜ。金貨十枚よこせば渡してやる。」";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "「ほら、どうぞ。」";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "金だと？何のためだ？俺は施しなんざしねえ。だが、代わりに二ポンド分の鋼鉄をくれてやるぜ！";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "よし、これがあんたのマンガローザだ。忘れるな、俺たちのことは見なかったことにしろよ。";
			link.l1 = "へっ。忠告なんざ要らなかったぜ。";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_6");
		break;
		
		case "Bandit_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_7");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "「見てみろ」 "+npchar.name+"「これが必要な植物か？」";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "俺が頼んだもの、持ってきたか？";
				link.l1 = "まだだ、今取りかかってるところだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "ああ、これで間違いない。これで必要なものはすべて揃った、さあ始められるぞ。";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "急いで行こう、時間を無駄にしちゃいけねえ。";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "船長、よろしければ、後でお話ししましょう。今は一番重要な時です……治療を始めます。";
			link.l1 = "もちろんだ、トーマス。娘さんが早く回復することを願っているぞ。";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+"「トーマスが自分の意思でお前を断ったわけじゃねえ。神父が、お前の助けを受け入れたら破門にすると脅したんだ。」";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "「すぐにわかったんだ」 "+GetSexPhrase("「あなた」","美しさ")+"、彼が重い心でその拒絶を私に伝えたのだ。";
			link.l1 = "教会を怒らせずに彼を助ける方法はあるか？";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "「ああ、」 "+GetSexPhrase("「あなた」","美しさ")+"、それは簡単なことじゃねえが、道筋は俺にわかってるし、どうすればいいかも知ってる。ただ、 お前の助けがなきゃ無理なんだ、わかるだろう。";
			link.l1 = "もちろん、俺に任せてくれ。";
			link.l1.go = "gypsy_10";
			link.l2 = "悪いな、黒い眉のあんた、だが俺にはこれにかまってる暇はまったくねえんだ。俺にできることは全部やった。 今は自分の用事を片付けなきゃならねえ。";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "それじゃあ、必要なものを言うぜ：あの娘の持ち物、ダチュラの茎を二本、イペカックの茎を一本、 そしてバーベナを一本だ。\nこれを全部持ってきてくれたら、あの娘のために治療薬を作ってやれるぜ。";
			link.l1 = "わかった、必要なものは全部用意するぜ。";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "トーマス、残念だが神父は俺の言葉を聞いてくれなかった。だが、ジプシーと俺ならお前を助けられるぜ。 俺が必要なのは……";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "「俺に教会に逆らえって言うのか？」";
			link.l1 = "俺たちはすべて静かにやる、誰にもバレやしねえ。\nもうすぐお嬢さんもまた人生を楽しめるし、若い娘らしく自由に町を歩けるようになるぜ。";
			link.l1.go = "Tomas_23";
			link.l2 = "くそっ、トーマス・モリソン、お前は本当に娘を回復させたいのか、それとも綺麗事の陰に隠れてるだけか？";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "わかった、承知したよ。しかし、頼むから慎重に行動してくれ。余計な噂や面倒ごとはご免だからな。";
			link.l1 = "もちろんです。では、あなたの娘さんが大切にしている私物が必要なんです。何か思い入れのある品をお願いします。";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "わかった、承知した。しかし、どうか慎重に行動してくれ。余計な噂や面倒ごとはご免だ。";
			link.l1 = "もちろんだ。だから、娘さんが大切にしている私物が必要なんだ。何か思い入れのある物を用意してくれ。";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "ふむ……よし！うまくいく方法を思いついたぜ。ここで待ってろ、すぐ戻るからな。";
			link.l1 = "待ってるぜ……";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("A few minutes later...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "ほら、これが翡翠のビーズだ。エスターは決して外さなかった、大切な品なんだ。";
			link.l1 = "素晴らしい。あとは待つだけだ。すぐに会おう、トーマス。";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "必要なものはすべて揃ったか？";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "必要なものはすべて揃えた。";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "何を持ってくればいいか、もう一度教えてくれ。";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "それじゃあ、必要なものを言うぞ：あの娘の持ち物、ダチュラの茎を二本、イペカックの茎を二本、 そしてバーベナを一本だ。\nこれらを全部持ってきてくれたら、あの娘のために薬草の煎じ薬を作ってやれるぜ。";
			link.l1 = "よし、必要なものは全部俺が用意するぜ。";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "素晴らしい。これであの娘のために治療薬を調合できる。薬ができるのは早くても明日の朝だ。\nいつものように、町の通りで私を見つけられるぞ。";
			link.l1 = "わかった、それじゃあまたな。";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "「さて、」 "+npchar.name+"、薬はもうできたか？";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "「そこにあるぞ。」 "+GetSexPhrase("「あなた」","美しさ")+"。娘にこの数珠を身につけさせ、この小瓶の中身を最後まで飲ませなさい。そうすれば、 遅くとも一ヶ月以内にすっかり元気になるだろう。";
			link.l1 = "これをすぐにトーマスのところへ持っていくぜ。じゃあな、黒眉。";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "トーマス、すべて準備できた。エスターはこの数珠を身につけて、この小瓶の薬を一気に飲み干すべきだ。";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "ありがとうございます。 "+pchar.name+"！どうかお許しください、私は一分たりとも無駄にしたくありません…";
			link.l1 = "「もちろん、もちろん。」";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "「ごきげんよう」 "+pchar.name+"「！うちのエスターが元気になった！すっかり健康を取り戻して、今は教会で、 あなたとジプシーを私たちのもとに遣わしてくださった主なる神に感謝を捧げているんだ！」";
			link.l1 = "トーマス、すべてうまくいって本当に嬉しいよ！あの娘のことを頼むぞ、 これからは長く幸せな人生が待っているんだからな。";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "この三百ドゥブロンを受け取ってください。\n残念ながら、これ以上はお渡しできません。この金を用意するために借金までしたのです。\nですが、どんな言葉や金でも、あなたへの感謝の気持ちは表せません、船長。\nあなたは彼女の命の不安から私を解放してくれただけでなく、私たち家族に未来への希望を与えてくれました。\n私はいつまでもあなたに借りがあるままです！";
			link.l1 = "ありがとう！三百ドゥブロンとはずいぶん気前がいいな、安心してくれ――これでもう十分すぎるほど礼はもらったぜ！";
			link.l1.go = "Tomas_43";
			link.l2 = "金は受け取らないぞ、トーマス。無理に渡そうなんて考えるな！その代わり、エスターにきれいなドレスでも買ってやれ、 あの子にはふさわしいからな。";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+"、いつでもお越しください。我が家はいつでもあなたを歓迎します。それから、ジプシーの女にも話しかけてください、 あなたに会いたがっていましたよ。";
			link.l1 = "光栄に思うぜ！さて、もう行かなくちゃならねえ――潮の流れはどんな船長も待っちゃくれねえからな。";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "もちろん、もちろん。神のご加護がありますように。 "+GetFullName(pchar)+"!";
			link.l1 = "さようなら。";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "あなたは本当に高貴なお方です "+GetFullName(pchar)+"！聖母マリアがあなたと共にありますように！ぜひまたお越しください、あなたはいつでも我が家の歓迎すべき客です。 そして、 "+pchar.name+"「ジプシーに話しかけてくれ、あの女があんたに会いたがってたぜ。」";
			link.l1 = "もちろんだ！さて、俺は行かねばならねえ――海が俺を呼んでるんだ。";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Have you heard? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison lights a candle in the parish daily for the health of "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison has blossomed before our eyes. As if she had never been ill. No one can really explain what made the illness retreat.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "「ほら、そこにいるじゃねえか」 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"！戻ってくると信じていたぞ。お前のおかげで、あの娘はすっかり元気になって、今では鳩のように動き回っている。 町中が彼女のことを驚きと共に語っているんだ。";
			link.l1 = "まあ、黒眉よ、俺だけの手柄じゃねえさ――あんまり俺を持ち上げるなよ。お前の薬酒があいつの体を回復させたんだ、だから自分の功績を過小評価するなよ。";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "「お前は優しい心を持ってるな」 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"、それに鋭い頭脳も持ってる！お前はきっと偉大になる――それが俺の予言だ。";
			link.l1 = "へっ……まあ、ありがとう。 "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "「ほら、ここにいるじゃねえか」 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"！またここに現れると思っていたよ。おかげであの娘は元気を取り戻し、今では鳩のように軽やかに舞っている。 町中が彼女に感心しているんだ。";
			link.l1 = "まあまあ、お前が自分であの娘を助けたんだろう？それなのに全部の手柄を俺に押し付けるつもりか？そりゃ無理だぜ！ 薬を用意したのも、お前が彼女を立ち直らせたのも全部お前だ。栄光はお前が受け取るべきだぜ。";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "「お前は優しい心を持ってるな」 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"、そして高貴な魂を持っている。あなたに贈り物がある――どんな船長でも喜ぶものだ。さあ、どうぞ。これでお前の船のネズミどもは、幸せも安らぎも得られねえぞ！";
			link.l1 = "俺に贈り物か？おいおい、まさかの展開だぜ！";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "お前の魂は清らかだな、一時の快楽のためにマンガローザを燃やすことはしないと見た。どうしても彼女が必要なら、 俺のところに来い。 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"。三本で三百五十ドゥブロンかかるぞ\nこの薬草は気まぐれで、誰でも見つけられるものじゃねえ。だから急かすな――月に一度以上は頼むなよ、どうせそれ以上は手に入らねえからな。";
			}
			else
			{
				dialog.text = "お前の魂は輝いているな。愚か者じゃないし、薬草の知識もそこらの医者に負けてねえ。いろんなものを見つけられるが、 運がいつも味方するとは限らねえ。珍しい植物で、誰でも見つけられるわけじゃねえものがある。「マンガローザ」 って呼ばれてるんだ。もしそれが必要になったら、俺のところに来な。 "+GetSexPhrase("ファルコネット","いちゃいちゃ")+"。三本は用意してやるが、タダじゃ渡さねえ――三百五十ドゥブロンはもらうぜ\nだがこの薬草は気まぐれだから、急かすんじゃねえ。月に一度以上は頼むな――たとえ運命のカードを全部並べても、早くは手に入らねえからな。";
			}
			link.l1 = "「まあ、ありがとう」 "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "船長、どうしても思ってしまうんです――きっと主ご自身があなたをこの時に導いてくださったのでしょう！あなたは私の娘を救ってくれました、 その恩は決して忘れません。";
			link.l1 = "たぶんそうだな、トマス。主の御心は計り知れない。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "ワインはいかがですか、船長？大切なお客様のために特別なものをご用意しております。";
			link.l1 = "ありがとう、トーマス、しかし残念ながら行かねばならない。";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "どうしたんだ、俺の鷹よ？";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "教えてくれよ、黒い眉のあんた、俺にマンガローサをくれるのか？";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "ちょっと挨拶に寄っただけだ。そろそろ行くぜ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "俺以外に誰がいるってんだ、 "+GetSexPhrase("「あなた」","美しさ")+"、そんな珍品が手に入ると思うか？三百五十ドゥブロンだ――それでお前のものだ、三本、これ以上もこれ以下もない。";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "値段は妥当だ。金貨はあんたのものだ。";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "くそっ！財布が軽すぎるぜ。運が向いたらまた戻ってくるさ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "それでいい。持っていけ。ただし、無駄に使うんじゃねえぞ、いいか――マンガローザはただの薬草じゃねえ、誰もが扱えるような力が秘められてるわけじゃねえからな。";
			link.l1 = "心配するな、黒眉よ。その力、俺がちゃんと役立ててやるぜ。";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}