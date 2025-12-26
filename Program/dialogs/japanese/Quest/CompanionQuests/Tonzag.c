void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
		
		case "startoff":
			dialog.text = "ド・モール船長！トルトゥーガへようこそ！";
			link.l1 = "ごきげんよう、中尉。仲間たちと海の景色を楽しんでいるのか？";
			link.l1.go = "startoff_joke";
			link.l2 = "下がれ、中尉。";
			link.l2.go = "startoff_silence";
			
			AddDialogExitQuestFunction("Tonzag_Arrested");
		break;
		
		case "startoff_joke":
			dialog.text = "船長、あんたの評判はすでに知れ渡ってるぜ。上の連中が、 俺たちの美しいトルトゥーガ島の見物ツアーを用意してくれたんだ。\nさっそく始めるぜ――まずは町の牢屋からな。あんたの部下たちも招待されてるぜ。";
			link.l1 = "副官、俺は浜辺で捕まえたみすぼらしい密輸業者なんかじゃねえ。冗談はやめろ。ちゃんと事情を説明しろ。";
			link.l1.go = "startoff_joke_1";
			link.l2 = "なら、時間を無駄にしねえぜ！案内しろ、副官！";
			link.l2.go = "startoff_joke_2";
		break;
		
		case "startoff_silence":
			dialog.text = "お前ら水夫どもには、別のやり方が必要みてえだな。\n兵士ども、戦闘の準備をしろ！\nド・モール船長、お前とその士官たちは逮捕する。武器を捨てろ！";
			link.l1 = "弾丸をくれてやるぜ――どこに欲しいんだ、少尉？お前ら陸ネズミには、それしか方法がねえんだよ。";
			link.l1.go = "startoff_silence_1";
			link.l2 = "どんな法だ？流血なしで武装集団を捕らえたいなら、もっと本気を出せ、少尉。";
			link.l2.go = "startoff_silence_2";
		break;
		
		case "startoff_joke_1":
			dialog.text = "俺から見りゃ、お前らはみんな同じだ……悪いが説明はねえぞ、船長。上からの命令だ。悪いが、武器を渡してもらおうか。";
			link.l1 = "今は揉め事なんていらねえ……今はな。奴らの言う通りにしろ。";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", +5);
		break;
		
		case "startoff_joke_2":
			dialog.text = "うっ……俺の言いたいことが伝わってねえみたいだな。船長、あんたとあんたの士官たちは逮捕されるんだ！武器を捨てて、 俺たちと一緒に来い！";
			link.l1 = "今は揉め事なんていらねえ……今はな。奴らの言う通りにしろ。";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "startoff_silence_1":
			dialog.text = "もう一言でも言ってみろ、船長。ここでお前を埋めてやるぜ。武器を地面に置け、今すぐだ！";
			link.l1 = "今は揉め事なんていらねえ……今はな。奴らの言う通りにしろ。";
			link.l1.go = "exit";
			
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "startoff_silence_2":
			dialog.text = "血なんざ怖くねえよ、船長。たとえ奇跡的に生き延びたとしても、もう二度とトルトゥーガの地は踏めねえぜ。\nそれに俺たちの軍の諜報によれば、お前はこの島への出入りを相当重視してるらしいな。";
			link.l1 = "今は面倒ごとはごめんだ……言われた通りにしろ。";
			link.l1.go = "exit";
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "船長、状況は最悪だぜ！敵にがっちり押さえ込まれてる、このままじゃ全員くたばるまで離してくれねえぞ！今、 仲間たちは本当に危機的状況だし、大砲の乗組員もほとんどやられちまった！\n";
			link.l1 = "俺があいつらを助ける。お前が指揮を取って、ここから脱出するんだ！";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "「ああ、旦那！」";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "勝利だ、船長！上陸部隊は全滅させたぜ、敵は退却を選び南へ向かった。船の状態は許容範囲だ。\n生存している乗組員： " + GetCrewQuantity(pchar) + " 人間ども。報告は終わったぜ！";
			link.l1 = "ありがとうよ！皆にラムを振る舞え、港に着くまで見張りを強化しろ！";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "おおっ！あいよ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		case "killer":
			dialog.text = "そして、本人が来やがったな！外の血まみれの虐殺を見たか？全部お前の仕業だ、裏切り者め！だがな、 全部のツケを払ってもらうぜ――ポルトベロのことも、グルオーのことも、この鉱山のこともな！";
			link.l1 = "待て、そりゃ一体どういう……";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_FightInMine");
		break;
		
		case "mine_head":
			dialog.text = "";
			link.l1 = "うぐっ！こりゃあ縁起が悪いぜ……";
			link.l1.go = "mine_head_1";
		break;
		
		case "mine_head_1":
			dialog.text = "サン・サンティアゴよ、俺を守ってくれ！\n悪党め！どんな化け物がこんなことをしやがるんだ？\n答えろ、旦那！";
			link.l1 = "落ち着け、旦那！まずは自己紹介しろ！ああ、ここでとんでもない虐殺があったが、それをやった連中はもう死んでるぜ。 俺が直々に奴らの死体で鉱山を“飾って”やったんだ…";
			link.l1.go = "mine_head_2";
		break;
		
		case "mine_head_2":
			dialog.text = "俺は " + GetFullName(npchar) + "「王立ロス・テケス鉱山の主任技師だ。数ヶ月に及ぶ任務から今戻ったばかりだが……なんだこれは！ここで起きたことは神と人類への罪だ、だからすぐに武器を捨ててもらうぞ。 カラカスの当局がこの悪事を調査する！」";
			link.l1 = " 従えねえぜ、旦那、そしてこの虐殺には俺は無関係だと誓う！だが、しつこくするなら、 てめえの死体も山に積み上げてやるぞ。";
			link.l1.go = "mine_head_3";
		break;
		
		case "mine_head_3":
			dialog.text = "俺は死を恐れちゃいねえが、退くべき時はちゃんとわかってるんだ。行け、だが覚えとけよ、 ここで起きたことは全部報告するつもりだ、一つ残らずな！";
			link.l1 = "それには同意できねえ、旦那。こんなことになっちまって悪いな。戦うぞ！";
			link.l1.go = "mine_head_fight";
			link.l2 = "死にたがってるようだな、旦那。だが今日は、これ以上誰も死なねえ。俺たちは引き上げるぜ、 このこともちゃんと報告書に書いとけよ！";
			link.l2.go = "mine_head_peace";
		break;
		
		case "mine_head_peace":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_LetMineHeadGo");
		break;
		
		case "mine_head_fight":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_FightMineHead");
		break;
		
		case "alonso":
			dialog.text = "「捕虜をどうする、船長？」";
			link.l1 = "特別なことはねえ、ただあいつを死なせたり逃がしたりすんなよ。";
			link.l1.go = "alonso_1";
		break;
		
		case "alonso_1":
			dialog.text = "あいよ！今日は尋問に俺が加わる必要はねえってことか、船長？";
			link.l1 = "なんでだ？職業でも変える気になったのか、アロンソ？";
			link.l1.go = "alonso_2";
		break;
		
		case "alonso_2":
			dialog.text = "ははは、いや、船長。俺はこの仕事が大好きだが、どうやらあんたの船には新しい腕利きが乗り込んだみたいだな！";
			link.l1 = "「エルキュール？そんな考え、どこから出てきたんだ？」";
			link.l1.go = "alonso_3";
		break;
		
		case "alonso_3":
			dialog.text = "さて、船長、あの爺さんがこのために道具箱を持ってきて、早速使ってくれたぜ。俺の道具を出す必要もなさそうだ。 ははっ！";
			link.l1 = "なるほどな……元の持ち場に戻れ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_DrinkAgain");
		break;
		
		case "captive":
			dialog.text = "ああ…シャルル・ド・モール。リーグ全体を代表して謝罪させてくれ。お前に手を出すなという命令が届いたのは遅すぎた。 俺たちの組織はお前に何の恨みもない、船長。だが、このハゲた獣については…うっ！お前の手綱につながれている限りは無事だが、俺からの忠告だ――そいつは手放して、ふさわしいドブの中で朽ち果てさせてやれ！";
			link.l1 = "推薦はありがたいが、俺が気になるのは、なぜ誰かがあんたの傭兵どもから俺を守っているのかってことだ。";
			link.l1.go = "captive_1";
		break;
		
		case "captive_1":
			dialog.text = "俺には分からねえよ、船長。たぶん新しい後ろ盾からの指示だろうな。知ってるか、裏切り者？ 今やリーグがまた頂点に立ったんだぜ！";
			link.l1 = "「そいつは誰だ？」";
			link.l1.go = "captive_2";
		break;
		
		case "captive_2":
			dialog.text = "俺には分からねえよ、船長。たとえ知ってたとしても、そういうことは口外しねえんだ。";
			link.l1 = "その場合は、他のことを話せ。そうすりゃ、どこへでも行っていいぜ。俺の言葉だ。";
			link.l1.go = "captive_3";
		break;
		
		case "captive_3":
			dialog.text = "そんな簡単にか？いいぜ、船長、質問があるなら聞けよ。それが済んだら俺を行かせてくれ。たとえ戻れたとしても、 もうリーグには戻らねえって誓うぜ。";
			link.l1 = "なぜそんなにエルキュールにこだわるんだ？たかが一人の脱走兵にしては面倒が多すぎるぜ。";
			link.l1.go = "captive_4";
		break;
		
		case "captive_4":
			dialog.text = "「てめえ、あいつに何を話したんだ、この野郎？すべてが見た目通りじゃねえんだぜ、船長！リーグは常に動いてるし、 暗号も変わる、雇い主もいろいろだ。出て行きたいのか？好きにしな！出口が閉ざされてるのは幹部連中だけだ、 このクズは一度もそんな立場じゃなかった。奥さんは別だがな、トンザグ夫人には俺たちも一目置いてたから、 彼女だけは特別扱いしたんだ。」\n";
			link.l1 = "「じゃあ、なぜだ？」";
			link.l1.go = "captive_5";
		break;
		
		case "captive_5":
			dialog.text = "ポルトベロでな、あれは大事だったぜ。お前の仲間はただ去ったわけじゃねえ、契約を破っただけでもねえ、 仕事を片付けに来た連中を殺しただけでもねえんだ。あいつは通りで本物の虐殺をやらかして、 カスティーリャ人との関係をとことんややこしくしやがった。あの日、善良なカトリックどもが味わった恐怖は、 普通の海賊襲撃じゃとても及ばねえ。くそ、もし他の誰かがやったなら、俺も感心したかもしれねえな。";
			link.l1 = "また虐殺か？面白いじゃねえか。続けろ。";
			link.l1.go = "captive_6";
		break;
		
		case "captive_6":
			dialog.text = "当時の会社副取締役ローデンブルクが介入した。どうにかして一件をもみ消すことに成功したが、 スペインの懲罰作戦で多くの優秀な仲間を失ってしまった。\nしかし、しばらく経つと、またやつらと取引を再開したんだ……ああ！だが、俺たちは何も忘れちゃいなかった。機会があればすぐにでも報復しようとしたのさ。すべての元凶、 トンザグは殺される運命だった。";
			link.l1 = "それはうまくいかなかったな。鉱山の方はどうだ？";
			link.l1.go = "captive_7";
		break;
		
		case "captive_7":
			dialog.text = "俺たちはやむを得ずやったんだ。あのクズどもを始末するには、あまりにも金がかかりすぎた――だから金が必要だった。全部あいつのせいだ……だが暗殺は失敗し、俺はロス・テケスに戻って後始末をしに来た……どうやって俺の居場所を突き止めたんだ？\n";
			link.l1 = "関係ねえ。お前らの頭と会う必要があるんだ。誤解は俺自身で片付けたい。お前らの謎めいた後ろ盾の保証なんざ、 いつ切れるかわからねえからな。";
			link.l1.go = "captive_8";
		break;
		
		case "captive_8":
			dialog.text = "きっとカラカスであんたをもう待ってるぜ、船長。ほら、俺は何も隠してねえだろ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog");
		break;
		
		case "captive_9":
			dialog.text = "アルノ司令官が死んだ。今はオースティンが指揮を執っている。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog2");
		break;
		
		case "captive_10":
			dialog.text = "お前の質問には全部答えたぜ、船長。約束は守れよ。";
			link.l1 = "行かせてやる。俺の船から降りろ、そしてカラカスで待ち伏せなんかされてねえことを祈るんだな。";
			link.l1.go = "captive_spare";
			link.l2 = "面白い話をありがとう。ただ、鉱山で見たことの後でエルキュールに虐殺の罪を着せるのはやりすぎだったぜ。\n地獄へ行け、お前の居場所はそこだ。";
			link.l2.go = "captive_execute";
		break;
		
		case "captive_execute":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ExecuteCaptive");
		break;
		
		case "captive_spare":
			DialogExit();
			
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin2");
		break;
		
		case "cureer":
			dialog.text = "旦那方、会合にご招待だ。教会で待っているから、警備は万全だぜ。";
			link.l1 = "早かったな……";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CureerGoAway");
		break;
		
		case "ostin":
			StartQuestMovie(true, false, true);
			PlaySound("VOICE\" + LanguageGetLanguage() + "\OliverTrast02.wav");
			dialog.text = "シャルル・ド・モール。エルキュール。お前はここから生きては帰れねえぞ。";
			link.l1 = "会話を始めるにはいい方法だな。お前、本当にこんなこと全部必要なのか？";
			link.l1.go = "ostin_1";
		break;
		
		case "ostin_1":
			dialog.text = "あんたの場合は、"+pchar.name+"船長、そう簡単にはいかねえんだよ。わかるか、新しい後ろ盾が「手を出すな」ってしつこく言ってきやがった……だが、そんな要求はケツにでも突っ込んでろってんだ！俺はあんたみてえな連中が大嫌いなんだよ！ 白くて綺麗な帆を掲げて、まるで氷が口の中で溶けねえみたいな顔しやがってよ。でもな、俺の刃がぶち込まれたときゃ、 みんな女みてえに悲鳴を上げるんだぜ。それがたまんねえんだよ、チャールズ、教えてやるよ！久々にやるが……今、目の前にいるじゃねえか、坊や。";
			link.l1 = "お前は病気だぜ、相棒。";
			link.l1.go = "ostin_2";
		break;
		
		case "ostin_2":
			dialog.text = "いや、行かせるわけにはいかねえ。だが、お前の仲間の方はもっと簡単だぜ――俺の手下どもにはあいつは必要ねえしな。だが、あいつの昔のリーグ仲間の何人かは、 まだ俺のやり方の効果に納得しちゃいねえ……きれいな会社で、きれいなドブロン金のために、きれいな仕事しかしてこなかった連中だからな。だが、 やつらの考えを変える方法はちゃんと知ってるぜ――大胆な罪人の首を皿に乗せて見せりゃいいんだ、ははっ！\n";
			link.l1 = "そんなことをする場所を間違えたな、この阿呆め。教会で本当に戦いを始めるつもりか？";
			link.l1.go = "ostin_3";
		break;
		
		case "ostin_3":
			dialog.text = "ああ、いいじゃねえか？連中に同情でもしてるのか？ロス・テケスほど儲からねえかもしれねえが、 楽しめりゃそれでいいだろう。神の家の壁を血で染めてやるぜ、アハハ！船長、たっぷり塗料を用意してくれよな。\n";
			link.l1 = "なるほどな。俺たちが羨ましいんだろう、狂ったネズミめ？俺たちの自由が妬ましいのか？女たちが俺たちに会えて喜び、 懐には小銭がジャラジャラしてるのが羨ましいんだろ？自分の姿を見てみろよ。 お前の雇い主はどこからお前を掘り出してきたんだ、豚野郎？誰が教会に入れてやったんだ？";
			link.l1.go = "ostin_4";
		break;
		
		case "ostin_4":
			dialog.text = "土でも食ってろ、このクソガキ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchVystrel");
		break;
		
	}
} 
