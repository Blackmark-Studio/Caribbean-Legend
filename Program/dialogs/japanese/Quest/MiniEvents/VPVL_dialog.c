
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"！失礼、あなたは帆船乗りか"+GetSexPhrase("または","おれっす")+"?";
			link.l1 = "俺は船長だ "+GetFullName(pchar)+"、お仕えいたします。";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "私はレア。レア・カルノ… "+GetSexPhrase("Monsieur","Mademoiselle")+" 船長、最近到着されたのですか？海で「コーモラント」という漁船を見かけませんでしたか？実は、私の夫…ピエールが…二日前に出航して、まだ戻っていないんです。";
			link.l1 = "「コルモラント」号？いや、そんな船には出くわしていない。その名前なら覚えているはずだ。お気の毒です、奥様。 ご主人がご無事で、ただ航路で遅れているだけだと願っています。";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "「コルモラン号」だと？ははっ！それは船の名前か、それとも船主のあだ名か？どっちにしても、 どちらも見たことねえな。";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "どう考えればいいのかわからない……こんなに長く帰ってこなかったことは今まで一度もないんだ。いつも必ず昼までには戻ってきたのに。今は……何かが起きたんだ。そんな気がする。";
			link.l1 = "当局に行け。奴らなら巡回船を出して沿岸の海域を捜索できるはずだ。";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "どう考えればいいのかわからない……こんなに長く帰ってこなかったことは今まで一度もないんだ。いつも必ず昼までには戻ってきたのに。今は……何かが起きたんだ。そんな気がする。";
			link.l1 = "当局に行け。やつらなら沿岸の海域を捜索する巡視船を派遣できるぞ。";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "「ああ、」 "+GetSexPhrase("Monsieur","Mademoiselle")+" 船長、もちろん私はすでに司令官に話しましたよ。でも、何の役にも立ちませんでした。彼はただ肩をすくめて……捜索に出せる船はないと言っただけです。\n私には？ここに立って、地平線を見つめて、待つことと……希望を持つことしかできません。";
			link.l1 = "まあまあ、レア夫人。まだ絶望するには早いですよ。私が一日ぐらいなら捜索のお手伝いができそうですわ。";
			link.l1.go = "Agree To Help";
			link.l2 = "そんなに心配することはねえだろ？もしかしたら朝の風に乗って、 どこかの魅力的な女の腕にでも飛び込んじまったのかもな。ちょっと散歩して、新鮮な空気を吸って、また戻ってくるさ。 ";
			link.l2.go = "bad joke";
			link.l3 = "助言が欲しいかい？そんなに地平線を睨み続けるのはやめておきな。ル・フランソワの酒場に行って、 旦那さんを探してみな。\n気を悪くしないでくれよ、たぶん旦那さんは家の悩みからちょっと逃げたかっただけさ。 それを大げさに悲劇にすることはないぜ。幸運を祈るよ。";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 船長、俺…どう感謝していいか分からねえよ…あんた…あんたには、これがどれほど俺にとって大事か分からねえだろ！みんなただ肩をすくめるだけで…でもあんたは…あんたは助けてくれるんだな。ありがとう！";
			link.l1 = "まだ礼を言うのは早いぜ。さあ教えてくれ――旦那は普段どこで漁をしてたんだ？決まった場所があったのか、それともあちこち回るのが好きだったのか？";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "魅力的な女性だって！？今が冗談を言う時だと本気で思ってるのか？あの人が困っているのは分かってる……それなのに俺の悲しみを笑うなんて！（泣く）今は世界中が俺に敵対している気分だ。誰も助けてくれない……誰も俺の心の重さを分かってくれないんだ。";
			link.l1 = "レア夫人、お願いです、お許しください。無礼なつもりはありませんでした！誓って、旦那様を探します。 どこから探せばいいか教えてください。";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "お前…？本当に俺を助けてくれるのか？";
			link.l1 = "もちろんです。あんな許しがたい、場違いな冗談を言った償いとして、これくらいはさせてください。";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "ありがとうございます。 "+GetSexPhrase("Monsieur","Mademoiselle")+" 船長。ありがとうございます……本当に驚きました――何と言えばいいのか分かりません……";
			link.l1 = "まだ礼を言うのは早いぜ。代わりに教えてくれ――旦那は普段どこで漁をしてるんだ？決まった場所があるのか、それともあちこち移動してるのか？";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "そうだな……ピエール……あいつは自分がどこで漁をしているか、めったに正直に教えてくれなかったんだ。「自分だけの秘密」だってさ。\nでも、もしあいつを見つける助けになるなら……たぶん……わからないけど……本当に助けるつもりなんだろう？ "+GetSexPhrase("Monsieur","Mademoiselle")+" 「船長？本当か？」";
			link.l1 = "ご主人の秘密の釣り場を教えるべきか迷っているのか？ご安心ください、ご家族の秘密は俺が守る。船長として誓うぜ。 捜索を始めるには、その場所を知る必要があるんだ。";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "「その通りだ」 "+GetSexPhrase("Monsieur","Mademoiselle")+" 船長……お許しください。あの場所はピエールにとって本当に大切な場所でした。彼はいつも、あそこが自分だけの秘密であり、 小さな宝物だと言っていました。\nでも、私には場所が分かります。彼を家に連れ戻す助けになるのなら……彼はル・マラン湾の近くで漁をしていました。南海岸沿いで、町からそう遠くありません。お願いします、 どうか彼を見つけてください！";
			link.l1 = "心配するな、レア。俺にできる限りのことは全部やるぜ。やつに敵がいたのか？最近誰かに脅されたことはあるか？";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "敵？ピエール？あの人ほど優しい人はいないよ！ハエ一匹殺せないくらいだ……ただの素朴な漁師さ。誰を怒らせることがあるっていうんだ？何が起きたのか全然わからない……すべてが奇妙で……怖いよ……";
			link.l1 = "怖がらないでください、Lea夫人。すぐに出発します。きっとご主人は無事です。必ずあなたの元へお連れします。どうか強くいてください。";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 船長、お願いです――何か知らせはありませんか？何か分かったことは？どんな小さなことでもいいんです！";
			link.l1 = "まだだ、残念ながら。だが、俺はまだ探してるぜ、レア！";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
			LocatorReloadEnterDisable("FortFrance_Town", "gate_back", true);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "まだ何が欲しいんだ？貧しい女をからかって、もう十分楽しんだんじゃないのか？";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 船長！ピエール！ああ、会えて本当に嬉しいわ！見つけてくれたのね！";
			link.l1 = "レア夫人、ピエール・カルノをお連れしました、ご本人です。無傷とは言えませんが、 あなたの手当てがあればすぐに元気になると確信しています。";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "ピエール！聖母マリアよ！お前のことが心配で気が気じゃなかったんだぞ！どこに行ってたんだ？顔色がまるでない……そんなに青白くなって……ああ！これは何だ！？このひどい傷は！？切り傷に……火傷まで……";
			link.l1 = "静かにしておくれ、私の大切な宝物よ。ほんのかすり傷さ、時が経てば消えるわ。もう一度あなたの顔が見られて……それだけが私の願いだったの。船長がいなければ……私は恩があるのよ\n "+GetSexPhrase("彼","彼女の")+" 俺の命そのものだ。";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" 船長……私……どう感謝したらいいか分かりません……彼を見つけてくださったんですね！私のピエールを救ってくれて……本当にありがとうございます！主があなたを見守ってくださいますように。 "+GetSexPhrase("Monsieur","Mademoiselle")+" 船長！";
			link.l1 = "さあさあ、もうその辺でやめとけ。ピエールに本当に必要なのは、温かい飯とちゃんとした休息だ。";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "くそっ！やっと姿を現しやがったな、 "+GetSexPhrase("この野良犬め","このあばずれ女め")+"「おい！どこほっつき歩いてやがったんだ？俺たちゃこのクソ暑い浜辺で三日も焼かれてたんだぜ！荷はどこにあるんだ！ ？」";
			link.l1 = "俺がいなきゃ宴は始まらねえってわけか、旦那たち？まあ、ちょっと遅れちまったが――潮に乗って来た方が、来ないよりはマシだろう！";
			link.l1.go = "Exit_Sneak";
			link.l2 = "俺に話しかけてるのか？下水ネズミみたいに吠える前に、礼儀ってもんを学んだらどうだ！";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experience gained", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experience gained", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+"、このボケナス貝！目を開けろ、この間抜け野郎――こいつは俺たちの連絡役じゃねえぞ！";
			link.l1 = "ううっ…また総督の飼い犬か！潮の満ち引きみたいに必ず現れやがる！それで "+GetSexPhrase("この悪党","この愚かな娘")+" 引きずられた "+GetSexPhrase("自分自身","彼女自身")+" ここだ、引っ張ろう "+GetSexPhrase("彼を","彼女の")+" 他のネズミと一緒に洞窟へ行くんだ。俺たちが見せてやる "+GetSexPhrase("彼","彼女の")+" どうやって秘密を吐かせるか――すぐに奴らは主人が夢見た汚い計画を全部ぶちまけるぜ！";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = "お前の頭の中でどんな汚ねえ妄想がうごめいてやがるんだ、この塩まみれの化け物め？よだれを垂らすのはやめろ！ あの娘は……例の奴に売ったほうがいい。あいつならこんな上玉の娘に箱いっぱいの金貨を出すぜ。 そうすりゃ俺たちは日曜が何度も来るくらい飲んで女遊びできるってもんだ！\n";
			if (pchar.sex == "man")
			{
				dialog.text = "デイヴィ・ジョーンズの金庫に何でまた新しい雑用野郎を牢に押し込む必要があるんだ？ そいつの仲間をもっと締め上げろ――夜明けのカモメみてえに全部吐くはずだ。\nこいつについては、今ここで腹を裂いてやろうぜ、顔を見る手間も省けるからな！";
			}
			link.l1 = "「千匹の腹ぺこサメがお前の内臓を食いちぎるがいい」 "+sld.name+"！お前はこの群島で一番ずる賢い密輸業者だぜ！";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("No pistol equipped", "NONE");
					link.l2 = "もしあのフジツボ頭があんたの一番切れるカトラスなら、 他の連中の脳みそにゃどんなイカれたデタラメが詰まってるのか、考えるだけでゾッとするぜ！";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = "（心の声）（ピストル）こいつら海のネズミどもがくだらねえおしゃべりに夢中になってる間に、 俺は澄み切った空に閃く稲妻みてえに、一撃で仕留めるチャンスだぜ。";
					link.l1.go = "murder";
					notification("Check passed", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Skill too low (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "もしあのフジツボ頭が一番切れるお前のカトラスなら、他の連中の脳みそにゃどんなイカれた戯言が詰まってるのか、 考えるだけでゾッとするぜ！";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "その生意気な舌、頭ごと切り落としてやるぜ、この野郎"+GetSexPhrase("","――汚らわしいあばずれ女")+ "「そしてカモメどもに食わせてやるから、二度と口をきけなくしてやるぜ！」";
			link.l1 = "掘り出してみろよ？さあ来い、悪魔と踊る度胸があるならな。";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"…許してくれ…頭が混乱してるんだ…奴らが始めたことを終わらせに来たのか？";
			link.l1 = "お前がピエール・カルノか？";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "ああ、俺がアユーだ。俺の名前を知ってるのか？";
			link.l1 = "もちろんだ。じゃなきゃ、俺がここにいる理由がねえだろう？";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "許してくれ、何もわからないんだ……痛みと飢えで正気を失ってしまった……なぜお前は来たんだ？";
			link.l1 = "簡単なことだ。お前が姿を消してからというもの、お前の忠実な妻は埠頭で見張りを続け、 コルモラン号の帆を探し続けていた。その悲しみがあまりにも深く俺の胸に刺さってな、見て見ぬふりなどできなかった――だからお前を探す決心をしたんだ。";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "俺の妻……愛しいレア……もう二度と会えないと思ってたんだ……";
			link.l1 = "潮はもう引いたぜ。あの娘はまだ希望を捨てずに桟橋でお前を待ってる。\nさあ、ここを出よう。俺の腕につかまれ。";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "「お慈悲を……」 "+GetSexPhrase("Monsieur","Mademoiselle")+"…少し休ませてくれ…足が流木みたいだ…本当に、ありがとう。あんたがいなけりゃ…まるで全能の神様があんたを遣わしたみたいだ…まだ名前を聞いてなかったな。俺の命の恩人を、どう呼べばいい？";
			link.l1 = "Captain "+GetFullName(pchar)+"。体力を回復している間に、どうしてこんな場所に来たのか話してくれ。お前はこいつら……男たちと取引でもしていたのか？";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "とんでもないですよ、船長。俺はただのしがない漁師です。今日は朝から調子が良かったんです。 西の岸辺で漁をしていたら、信じられないほど大漁でしてね。\n魚を樽に詰めて、もう一度網を投げようと夢中になっていたら、 潮の流れが船を暗礁の方へ引っ張っているのに気づきませんでした。船体は卵の殻みたいに薄くて、 一度ぶつかっただけで海水が入り込んできました。朝獲れた魚で重くなったカツオドリ号は、 あっという間に沈んじまいました。";
			link.l1 = "それで陸に上がったら、密輸業者どもに総督の間者と勘違いされたってわけか？";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "その通りだ。呪われた波に打たれて、やっとの思いで岸にたどり着いたんだ。町へ向かう前に、 ただ体を乾かして休みたかっただけさ。そしたら、あの悪党どもがどこからともなく現れたんだ。\n奴らは俺を一目見てスパイだと決めつけやがった。何も言う暇もなく縛り上げられて、ここまで引きずられてきたんだ。 二日間も飢えさせられ、拷問されて、知らないこと――仲間や計画について――白状させようとしたが、俺は何も知らなかったんだ！";
			link.l1 = "あいつらには知恵が足りなかったからな――今ごろカニの餌になってるってわけだ。\nだが、それももう過去のことだ。お前は自由だぜ。さあ、奥さんのもとに戻る時だ――きっと心配でたまらないはずだぞ。";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "もう一度あの子を抱きしめたいだけなんだ。\nたぶん……たぶん今なら歩ける気がする。";
			link.l1 = "それじゃあ、これ以上時間を無駄にしないでおこう。";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "船長、お願いです――明日の晩、六つの鐘の時に酒場へ来てください。きちんとお礼を申し上げなければ、 私の良心が決して休まることはありません。\n今は……胸の内を言葉にできません。どうか、来てください。私にとってとても大切なことなのです。";
			link.l1 = "よし、ピエール。心配するな――俺が必ず行く。";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "船長！来てくださったのですね！どうぞ、ご一緒に！";
			link.l1 = "喜んで！";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "お前さんのこれからの幸運と健康に、俺たちのジョッキを掲げようぜ！";
			link.l1 = "俺のだけじゃなくて、ピエール、お前の命にも乾杯だぜ。あのみすぼらしい洞窟で見つけた時より、 ずっと元気そうじゃねえか。乾杯！";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "船長、俺の感謝の気持ちは言葉では表せねえ！見捨てず、背を向けず、 まったくの他人であるこの貧しい漁師を助けてくれたんだ。こんな高潔な行いには、それにふさわしい報酬が必要だ。 だから、俺の持ってるものをすべて差し上げたい。\nほら――太陽のように輝く琥珀が二十個と、沈没船から引き上げた珍しい青い石が五つ。今は全部あんたのものだ。\nそれと、俺の航海用の道具と釣り具も受け取ってくれ。もう船もない俺には、何の役にも立たねえからな。";
			link.l1 = "ありがとう、ピエール。これはきっと役に立つだろう。\nだが何よりも、お前が無事に帰ってきたことが一番だ――もう奥さんも恐れる必要はない。\nこれからは二人にとって良い方向に向かうはずだ。";
			link.l1.go = "PierTakeGift";
			link.l2 = "ピエール、その気持ちはありがたいが、お前が持っていろ。船を修理したり、道具や網、 樽を買ったりするのに一枚でも多く必要だろう。お礼の言葉と、お前と奥さんがまた一緒になれた姿、 それだけで十分な報酬だ。お互いを大切にしろよ。";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "俺はいまだにこれが本当に起こったことだとは信じられねえ……\n俺の家族の新たな門出、そしてお前の高貴な心に乾杯しようぜ、船長！";
			link.l1 = "幸運を祈るぜ、ピエール。俺たち全員に少しは運が必要だろう！";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "船長、こんなままでは終われません……あなたは私の命の恩人です、全てをあなたに借りています。琥珀や他の贈り物を受け取ってくれないなら、 せめて浅瀬での漁のやり方をあなたの船員たちに教えさせてください。それなら彼らの食事にもなり、 食料の出費も減ります。どうでしょうか？";
			link.l1 = "そりゃあいい考えだな！昔から言うだろ――網の投げ方を教えれば、その者は二度と飢えることはねえってな。";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "見事なお言葉だぜ、カピテン！役に立てて嬉しいぜ。さて――もう一杯やるか？";
			link.l1 = "ピエール、君の健康と繁栄を祈って！";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Four hours have passed...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "ネプチューンの髭にかけて！こいつは強烈なグロッグだぜ！もう一口、二口飲んだら…ひっく…俺はクラーケンも目を覚ますようなシャンティを歌い出しちまうぞ！ここから港まで、みんなに俺の声が響き渡るぜ！";
			link.l1 = "その歌は凪のときまで取っておけ、ピエール。声は……ひっく……次の寄港地まで取っておくんだ。お前が騒ぎ出したら、俺もすぐに合唱に加わっちまうぜ。それに……ええと……急ぎの用事があるんだ。潮は誰も待っちゃくれねえ……ひっく……酔っ払っててもな！お前もいい天気でいろよ……ひっく……それから、お前のいい女もな！";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Ship's provisions consumption reduced by 15%", "None");
			}
			else
			{
			dialog.text = "ネプチューンの髭にかけて！こいつは強烈なグロッグだぜ！もう一口か二口飲んだら…ひっく…クラーケンを叩き起こすようなシャンティを歌い出しちまうぞ！ここから港まで、全員に俺の声が聞こえるだろうさ！";
			link.l1 = "嵐のときに歌なんぞやめとけ、ピエール。声は……ひっく……次の寄港地まで取っとけよ。お前がわめき出したら、俺もすぐに合唱隊入りだぜ。それに……ええと……急ぎの用事があるんだ。潮は誰も待っちゃくれねえ……ひっく……酔っ払いだろうがな！お前も無事でな……ひっく……あのいい女房も大事にしろよ！\n";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "ああ、船長……お前さんは……ひっく……本物の船乗りの心を持ってるぜ！俺の借りは一生返せねえ、わかるか？もしまたうちの港に錨を下ろすことがあったら……うちの炉端は……炉端はお前さんのもんだ、まるで同じ……同じ母親から生まれた兄弟みてえによ！俺の魂と名誉にかけて誓うぜ！また運命の女神がこの岸にお前さんを導いたら、 一緒に酒をあおろうじゃねえか！";
			link.l1 = "しっかり頼むぜ、ピエール！俺は……ひっく、船酔いで足がグニャグニャになる前に錨を上げたほうがよさそうだ。 この酒場の床で漂流する羽目になっちまうからな！順風があんたの帆を満たしますように！";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "おおお、深き青き海よ～、順風満帆…ひっく…漁場へと夜明けとともに出航だぁ！…くそっ、ラムで頭が回らねえ！歌詞が思い出せねえ！船長！…まだここに停泊してるのか？酒場の親父！…ひっく…お前の蔵で一番の西インドの酒を持ってこい！\n";
			link.l1 = "出航するぜ、ピエール！ひっく……まだ自分の船までの危険な道を座礁せずにたどり着けるうちにな！";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"！この潮風に焼けた目には嬉しい光景だぜ！カリブ一の極上の酒を一杯どうだ？人生という大海原で出会えた記念によ！";
			link.l1 = "お前の風に焼けた顔を見ると、俺の心も嬉しくなるぜ、ピエール。だが、 あいにく今日は義務があるから酒は控えねばならん。これから危険な海域を航海するには、 澄んだ頭と確かな手が必要なんだ。\nまた次に運命が巡り合った時にな。";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "あよう、あよう、船長！船はまず航海してからでないと港に着けねえぜ。商人どもが言うように、帳簿が先、遊びは後だ。 でもな、運命の女神がまた俺たちに微笑んだ時には、あの黒ひげも誇りに思うような祝杯をあげようじゃねえか！";
			link.l1 = "船の航海日誌に記しておけ、ピエール。潮の流れがまた俺たちを引き合わせるその時まで！";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "船長！お前さんの船は義務という嵐から無事に港へたどり着いたのか？";
			link.l1 = "商売の波がまだ俺の錨を引っ張っているんだ、ピエール。しばらくは義務に縛られて舵輪から離れられねえよ。";
			link.l1.go = "Exit";
		break;
	}
}   