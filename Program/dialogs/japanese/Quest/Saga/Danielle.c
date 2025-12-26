// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "待って、イケメン！ちょっと話したいんだけど。";
			link.l1 = "お前に見覚えがあるか？まあ、どのみち淑女のためなら、いつでも少しくらい時間は空けているよ。";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "まだ予定を立てるな、船長。もう少し若くておバカそうな娘でも探して、あと数時間楽しんでなさい。 私にはあなたに頼みたい用事があるの。実は私、結婚しているのよ。夫の名前はネイサン・ホークよ。";
			link.l1 = "そりゃすごいな！ってことは、あんたが……ええと、ダニー・ホークだな、スヴェンソン旦那が言ってたやつ。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "この目で見ているわ。そうよ、森の悪魔が私のことを大した存在だと思っていないのは知っている――私も同じ気持ち。でも、私がサーベルを腰に下げているのは飾りじゃないって、あいつも警告せざるを得なかったのよ。 だから、回りくどいことはやめて、はっきり言いなさい、坊や！\n私はしばらくスヴェンソンと彼の客人たちの後をつけていたの。だって、 あいつが私の夫をジャングルに送り込んで死なせた張本人だから。最初はジャックマンと組んでいると思っていたけど、 今は違うと分かったわ。あなたたちの会話の間、私は窓の下に隠れていたの。全部は盗み聞きできなかったけど、 役立つ情報はたくさん手に入れたわ。\n本当に私の夫を探し出して、ジャックマンを懲らしめてくれるつもり？それとも、ただ大きなことを言っていただけ？";
			link.l1 = "盗み聞きはいけませんよ、ホーク夫人。しかし、もっと敬意をもって私に接してくだされば許しましょう。 私がホークを探しているかどうかは、私だけの問題です。何か有益な話があるなら話しなさい、 なければ私に構わないでください。二度は言いませんよ。";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "あはは、ずいぶん血の気が多いな！さあ、船長…俺の気性の激しさがあんたを居心地悪くさせてるのは確かだろうな。でも、あんたが臆病者じゃなく、 自分の価値をわかってるのも見て取れる。さて…自己紹介といこう。あんたに対しては言葉に気をつけると約束するぜ。俺にはあんたが必要だし、あんたにも俺が必要だ。 俺たちの目指すところは同じだろう。俺を仲間に入れてくれれば、絶対に後悔させない。ナサンを見つけるまで、 誠実と忠義をもってあんたに仕えると誓うよ。";
			link.l1 = "受け入れてやるとしよう……ダニー。スヴェンソンから、すでに旦那を探していると聞いたぜ。何か面白い情報でも見つけたか？";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "大したことじゃないけど、ジャックマンが嘘をついていると非難するには十分よ。あの野郎は、 私のナサンが相手をした鉱山の護衛たちは捕虜を取らないと言っていたわ。でも、 誰も私の夫の遺体を湾で見ていないのは確かだけど、それもそのはず、 実際には彼は捕虜として鉱山に連れて行かれたのよ。ミスキート族のシャーマン、スネークアイがそこで彼を見つけたの。 \nそれに、彼は夫の脱出も手配してくれたわ。でも今、夫がどこにいるのかは分からないの。 シャーマンはククルカンとかいう何かに食われたとかブツブツ言ってたけど、私にはさっぱり分からなかったわ。それに、 その現地人は白人の女なんて冗談だとでも言いたげだった。あなたが彼と話してみたら？もしかしたら、 あなたにはもっと話してくれるかもしれないわ。";
			link.l1 = "それは少しは救いだな！そういう知らせは俺を元気づけるぜ。このインディアンはどこで会えるんだ？";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "ジャングルの奥深くに村がある。アマティケ湾に上陸して、ジャングルを西へ進む必要があるんだ。 自分で見つけられないなら、俺が道を案内してやるよ。村からそう遠くない場所に石の偶像があって、 野蛮人たちはそれを神として崇めている。俺は何度かそこへ行ったことがあるが、特に珍しいものじゃない。 ただ苔に覆われた素朴な石さ。";
			link.l1 = "面白いな。よし、行こう。シャーマンと話して、次にどうするか決めようぜ。準備はいいか？";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "もちろん！もちろん、準備はできているよ。マルーンタウンを出てからずっと旅をしてきたんだ。それに、 あんたのただの乗客の一人にはなりたくないからね。";
			link.l1 = "いいだろう。俺の船に行こう。";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "了解だぜ、船長！";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"「さあ、来いよ！インディアンのシャーマンが話してた石像を見せてやる。ただの普通の石柱だぜ。行こう！」";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "おい！見てみろよ、ただの石像だぜ。別に珍しくもねえ……";
			link.l1 = "なるほど……でも、一番上の像はちょっと不気味じゃないか？ ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "インディアンの像はどれも不気味で邪悪な顔をしているな。前にも似たようなのを見たことがあるが、どれも同じだ。\nまあ、とにかく行こう、村はすぐ近くだぜ！";
			link.l1 = "行くぞ！";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "それで、どうだ、 "+pchar.name+"？あの赤肌の腹話術師はお前に何を言ったんだ？奴の哲学的な言葉から何か得たのか？";
			link.l1 = "また盗み聞きしてたのか、ダニー？";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "ええ…少しだけね。ほら、女ってそういうものよ。でも分かってほしいの、私はただ夫のことが心配なだけ。実際、 彼のことを愛してるのよ。だから盗み聞きしてたって、別にいいでしょ？それより、何か役に立つ情報は手に入った？";
			link.l1 = "考えているんだが……スネークアイの言うことは簡単には理解できなかった。しかし、どうやら村に入る途中で見たあの偶像は、 人を転送できる魔法のポータルらしい。";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "そんな目で俺を見るなよ。俺の考えじゃねえし、今のところ頭は無事だぜ。 お前がシャーマンに何を言われたか聞いたから、教えてやってるんだ。";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "どうか、お許しください。もうそんな目であなたを見ることはしません。どうぞ、続けてください。";
			link.l1 = "ナサンが追っ手にもう少しで捕まりそうになったとき、インディアンが救いの手段としてその像を見せ、「ククルカン」 と呼び、ナサンを丸ごと飲み込んで別の場所に吐き出したと言ったそうだ。\n簡単に言えば、ナサンはその像によって転送されたらしい。";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "なんてこった……ネイサンと俺は以前にも似たような厄介事に巻き込まれたことがあるんだ、そして今また同じことが起きてる。 あのマヤの魔法で満ちたインディアンの神殿で、もう十分な冒険を味わったはずなのにな…";
			link.l1 = "今なんて言った？";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "「ああ、なんでもないさ」 "+pchar.name+"、どうでもいいさ。俺の荒れた若い頃の思い出にすぎねえ。だが、どうしてネイサンはあんなことができたんだ？つまり、 テレポートだよ。俺たちはあの偶像のそばにいただけで、俺はその周りを歩き回って触ったりしてただけだ……ただの石じゃねえか！";
			link.l1 = "スネークアイが言うには、その偶像は真夜中になると命を吹き込まれるそうだ。\nその時だけ、ククルカンの精霊が宿り、黄金色の光を放ち始めるんだ。\nその時には触れてはいけないって話だが……いや、もしかしたら、触れるべきなのかもな……";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "不気味だな……さて、どうする？真夜中まで待ってからジャングルに入るか？";
			link.l1 = "いいや。シャーマンによれば、その偶像は人を転送するだけでなく、命も吸い取るらしい。私の理解では、 健康を奪うという意味だ。スネークアイはこの像を三度くぐり抜けて、そのたびに何か特別な薬で自分を癒やしていた。";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "「この薬を彼に頼んだのか？」";
			link.l1 = "もちろんだ。しかし、まず第一に残りのフラスコは三つしかなく、 第二に彼はそれらと引き換えに三つの護符を要求したんだ。";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "薬なしでやってみるのはどうだ？夜に像のところへ行って、触ってみよう…";
			link.l1 = "危険すぎる。確かにあのインディアンは少し正気を失っていて、俺たちをからかっているかもしれないが、 サイコパスには見えないから、奴の言うことは本当だと思う。\n君はインディアンの魔術について何か話していたな……その存在を疑っているのか？";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "ああ、そうだった。自分の目で見たから疑いはない。だから、お前の言う通りだな、わざわざ危険を冒す必要はない。";
			link.l1 = "その通りだ。だからこそ、まず俺たちがアミュレットを見つけてから、 シャーマンからあの素晴らしい薬を手に入れて像のところへ行く。俺が行く。一人でな。";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "なぜだ？それに俺はどうなるんだ？";
			link.l1 = "俺がいない間、お前は俺の船に残って指揮を執るんだ。反論なんてするなよ、ダニー。例の薬は三つしかないんだ。 もしシャーマンの言う通りこれが本当に動くなら、ポータルがどこに繋がっているかも分からない。もしかしたら、 そこでナサンを見つけることすらできないかもしれない。";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "あなたはネイサンと同じね。男なんてみんな一緒だわ……いいわ、承諾する。";
			link.l1 = "お互いに理解し合えてよかった。\nさあ行こう、アミュレットを探さなければならない。";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "それで？薬は手に入れたのか？";
			link.l1 = "はい。薬といくつかの指示を手に入れた。あとは真夜中にあの偶像のところへ行って、触れるだけだ。";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "怖いのか？";
			link.l1 = "はい。残念ながら、あの呪術師はただの狂人かもしれないし、転移なんて起こらないかもしれません。";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "ほうほう……本当に怖くねえのか？ちっともビビってねえのか？";
			link.l1 = "ダニー、あまり詰め寄るなよ……どうしても知りたいなら、そうだ、正直に言うと自信がないんだ。";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "私も一緒に行く。";
			link.l1 = "また口論を始めるつもりか？話はついたと思ってたんだが…";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "私の言いたいことを誤解しているな。私はあんたのそばにいるだけだ。像がちゃんと機能するか……それとも機能しないか、確かめる必要があるんだ。";
			link.l1 = "異論はない。しかし、もし像に“食われる”ことがあっても、絶対についてくるんじゃないぞ。わかったか？";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "はい、約束します……あなたの後をつけたりしません、船長。";
			link.l1 = "よし。で、ダニー、どうやら噂ほど嫌な女じゃないみたいだな。";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "「俺のことをよく知らねえな」 "+pchar.name+"。しかし今はその話はやめておこう。";
			link.l1 = "やめておこう……まあ、夜の旅に備えて準備しよう！";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "「見ろ、」 "+pchar.name+"！神に誓って言うが、像の上に奇妙な光があるんだ！";
			link.l1 = "どうやらシャーマンは嘘をついていなかったようだな。\nそれに、この闇が俺を惑わせていないなら、像の頂上はもう石のようには見えなくなってきているぜ。";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "まさに……まるで純金でできているみたいだ！信じられない！";
			link.l1 = "時が来たぞ、ダニー。俺の幸運を祈って、指を交差してくれ。偶像には近づくな！ここにいろ。";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "「幸運を祈るぜ」 "+pchar.name+"…うまくいくといいが……シャーマンの薬は用意したか？";
			link.l1 = "ああ、ここにあるよ。大丈夫だ、ダニー。さて、行くぞ！(Tキーを押して偶像を起動)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "あ、あ、ああ？！くそっ！お前はいったい何の化け物だ、畜生め！？くたばれ！ 俺は今までにもっとひどい化け物を見てきたんだぜ、ヴァン・デル・デッケン本人も含めてな！ 今からお前の望み通りにしてやるよ！\n";
			link.l1 = "（かすかに）ダニー、待って！やめて！今すぐ！";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "（かすかに）ファン・デル・デッケン？うはははは！あの虫けらはすでに俺の手下だ！次はお前の番だ！俺にひれ伏せ、 忠実なるしもべよ！お前が俺の死者の軍勢を率いるのだ！\n";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "あ、あ、あ、あ、あ、あ、あ、あ、あ、あ、あ、あ、あ！どっか行け！今こんなこと、ありえないだろう！";
			link.l1 = "（かすかに）ダニー、待って！やめて！今すぐ！";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "あっ！？何だと！？ダニー？";
			link.l1 = "（かすかに）やめなさい！剣を収めて！これを外させてくれ！";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "くそっ、この化け物め、まるで…… "+pchar.name+"?!";
			link.l1 = "（かすかに）ああ……そうなのかい！";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "なんだよ、死ぬほど驚かせやがって！あと少しでお前をサーベルで斬り捨てるところだったぜ！";
			link.l1 = "俺は見たぜ……で、なんでそんなに熱くなってんだよ、あんた？";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "それが私なのです……ああ、胸がまだ高鳴っておりますわ……";
			link.l1 = "ダニー、今どこだ？ミスキート村から遠くないよな？";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "他にどこがあるってんだ！これがあんたを消した像だぜ。あれは見事だった！一生忘れねえよ。";
			link.l1 = "なるほど、ずっとここで私を待っていたのですか？";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "教えてくれ、俺は他に何をすればよかったんだ？像がお前を飲み込んじまった後は、 いつか吐き出してくれることを願うしかなかったんだぜ。それに、スネークアイが「こうなるのが一番あり得る」 って言ってたんだ。\n俺はミスキート族と一緒に暮らして、毎日あの偶像を見張ってた。こんな馬鹿げた話をなぜ今さらするんだ？答えろよ！ 外で何があった？どこに行ってたんだ？";
			link.l1 = "ダニー、この話はあまりにも長すぎるんだ、俺はいろいろ見てきたからな……でも、胸のつかえを下ろすために言うぜ、ナサニエルを見つけたんだ！";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "ナサンを見つけたのか？どこにいる？それに、無事なのか！？";
			link.l1 = "嘘はつかない――彼は生きているが、かなりひどい状態だ。コマンチの薬もなく、あの偶像にすべての力を吸い取られてしまった。 今は奇妙な「見捨てられた船の島」の、古くて壊れた船の船室で横たわっている。俺もそこに転送されたんだ、 だからスネークアイの言っていたことは正しかったんだな！";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "可哀想なネイサン……あの忌々しい島はどこだ？どうやって行けばいいんだ！？やっぱりあの偶像しか道はないのか？ ミスキート族から体力回復薬を全部買い占めて、今夜行ってみる！何とかしてみせる……";
			link.l1 = "止まれ！待て！ネイサンは病気だが、命に別状はない。若い者が一人、彼の世話をして食事も与えている。 もしあの偶像を通り抜けたら、健康を損なうぞ。それにこの島は本当に危険だ。あまりにも危険すぎる！";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "「それで、どうしろと言うんだ？ナサンが苦しんでいる間、いや、もしかしたら死にかけている間、 俺たちは何もしないでいろってのか？」";
			link.l1 = "取り乱すのはやめなさい。まず、ナタンは病気だと言ったが、死にかけているわけじゃない。私が本人と話した。次に、 私が島へ向かって航海するつもりだから、あなたも一緒に来てもらうわ。";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "その島がどこにあるか知っているか？";
			link.l1 = "ああ、もちろんだぜ！そこではネイサンだけじゃなく、シャーク・ドッドソンも見つけたんだ。島のおおよその座標と、 周囲のリーフを避ける航路も手に入れた。\nさあ、これから俺の船に戻ってブルーヴェルドへ向かうぞ…";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "何のためだ？なぜ今すぐ島へ直行できねえんだ？";
			link.l1 = "ダニー、遠征を組織する必要があるんだ。島では食糧が深刻に不足しているから、 できるだけ多くの食料を買い込むつもりだ。その後、島のリーフを越えられる船を選ばなきゃならない。 すべての船があそこを航海できるわけじゃないからな。それと、まずはスヴェンソンと話をしたいんだ…";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "準備にはそれほど時間はかからないさ。島はここから遠くない、ハバナの北西でメキシコ湾の東にあるんだ。";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "……わかったわ。じゃあ、やりましょう。あなたがネイサンを見つけてくれた、それが一番大事なことよ。ありがとう！ あそこにいる彼は体調が悪いのかしら？";
			link.l1 = "うーん……彼は病気なんだ。それに加えて、落ち込んで絶望している。君のことを恋しがっているよ。\nそれから、ネイサンが「君のことをとても愛している」と伝えてほしいって頼まれたんだ。";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "（涙をぬぐいながら）年寄りの馬鹿め！俺の言うことなんて、全然聞きやしなかったんだ…… "+pchar.name+"、さあ君の船へ行こう！できるだけ早く出航したいんだ！";
			link.l1 = "ああ、ダニー。俺の冒険の話もしてやるぜ。行こう！";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "こんな場所は今まで見たことがない。島全体が船でできているんだ！";
			link.l1 = "「そのことは話しただろ、ダニー…」";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "だが今は自分の目で確かめられる。\nそれはともかく、ナサニエルがどこにいるか教えてくれないか？";
			link.l1 = "奴は船の一隻の中にいる。\nだが、そこまで泳いで行かねばならん。";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "興味ない。どうやってその船に行けばいいか教えろ。";
			link.l1 = "ダニー、落ち着いてくれ。君もナサンも長い間待っていたんだから、もう少しだけ我慢してくれ！ 私が彼のところへ案内するよ；君たちだけじゃ絶対に見つけられない。 ナーワルやリヴァドスに出くわしてほしくないんだ；君が彼らと口論になったら、ろくなことにならないからね。";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "よし、じゃあ行こうか。俺がお前についていくぜ。";
			link.l1 = "泳ぐことがたくさんあるのを忘れるなよ。";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "大丈夫、私が何とかする。";
			link.l1 = "それは良かった……すぐに旦那に会えるぞ！";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "ネイサニエル…ネイサン！くそっ！私の愛しい人…";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "イエス様、自分の姿を見てみろよ……どうしてそんなことを自分にしたんだ？！……（泣きながら）私の言うことなんて全然聞かないんだから、全然！あのジャングルに入るなって言ったでしょ！ それなのに結局行ったじゃない！どうしてなの、ネイサン？！";
			link.l1 = "ダニー……すまない。仕方なかったんだ、わかってくれるだろう……";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "知ってるわよ！ああ、神様、あなた…一体何があったの！？（涙ながらに）大丈夫よ、あなた、全部きっとうまくいくわ…私がここにいるから。ミスキート族のところへ、スネークアイのもとへ連れて行くからね。 "+sld.name+"  呪術師があなたを癒やせるって聞いたんだ。俺たちには船もある……すべてうまくいくさ！";
			link.l1 = "ダニー、愛しい人…私の愛よ！あなたがそばにいてくれて、私は半分だけ癒されたわ。あなたの言うところなら、どこへでも行くわ。 スネークアイのところなら、そこへ行きましょう。";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "荷物をまとめろ。ああ、俺はなんて間抜けなんだ……空き瓶以外に詰めるものなんて何もない。ネイサン……";
			link.l1 = "「ダニー……」";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" …ナサンと私が騒ぎを起こしたことをお許しください。";
			link.l1 = "ダニー！何を許すって？大丈夫だよ。自分の気持ちを恥じているのかい？";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "いいえ、私は違います……ただ、その……";
			link.l1 = "この場面のことは誰にも知られやしない。約束するよ。ナサンに何が起きたかも誰にも分からないさ。\nマルーンタウンの海賊たちは、強くて手強いナサニエル・ホークを見ることになるんだ！";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "「ありがとうございます。」 "+pchar.name+"！あなたには恩があるわ……旦那を船まで連れていくわ。心配しないで、道は覚えているからちゃんと連れて行けるわ。彼をベッドに寝かせて、 私もそばにいるわ。あなたがここでやるべきことを全部終えたら、私たちはスネークアイへ出航するわ。ナサン、 私は彼が回復できると信じているの。";
			link.l1 = "わかったよ、ダニー。どうせ長居はしないしな。ほんとに手伝いはいらないのか？";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "私は確信しているわ。私たちは船にたどり着くわよ。\n心配しないで、絶対に旦那を死なせたりしないわ！";
			link.l1 = "ダニー、君は……素晴らしいよ！";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "（涙をぬぐいながら）行って…ただ行ってくれ\n "+pchar.name+"……それから、ここで時間を無駄にしないでください！";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "それで？あの人は私の夫を治してくれるの？教えて、治してくれるの！？";
			link.l1 = "ダニー、ネイサンはここに残らなきゃならない。一人でな。シャーマンは儀式の間、 誰にも邪魔されたくないと言っていた。それはお前にも当てはまる。 彼はナサニエルを一ヶ月以内に癒すと約束してくれたんだ。";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "「知ってるか、」 "+pchar.name+"、やっとまた自由に息ができるわ。シャーマンが夫を元の状態に戻してくれると強く信じているの。 もしスネークアイがナサンを癒せないなら、誰にもできないから、私は迷わずここにナサンを残していくわ。";
			link.l1 = "大丈夫だよ、ダニー。スネークアイは俺に嘘をついたことがない。俺はあいつを信じてる。";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "俺もだ。しばらくお前と一緒にいるぜ。 "+pchar.name+"、それで本当にいいのか？まだあの野郎ジャックマンを見つけなきゃならねえだろう。全部の元凶はあいつだ。 待ち伏せを仕組んだのもあいつだ！マルーンタウンでネイサンの代わりをやってたのもあいつだ！俺たちのフリゲート艦『 センチュリオン』を奪ったのもあいつなんだ！\n";
			link.l1 = "同感だ。ジャックマンを何とかしなきゃならねえ。ジャックマンが死ぬまでは、俺たち全員安全じゃねえんだ。だが、 あいつを殺すのは簡単じゃねえぞ。";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "「何か予定でもあるのか、」 "+pchar.name+"?";
			link.l1 = "まだだ。ヤン・スヴェンソンのところへ行って、助言をもらわないといけない。ひとつずつ片付けよう、 まずは昇進しないとな\n "+sTemp+" まずはカリブ海兄弟団の首領のもとへ行くんだ。だから、そのためには全ての海賊男爵から票を集める必要がある。";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "よし、スヴェンソンのところへ行こう。あのじじいが何を言うか聞いてやろうじゃねえか…";
			link.l1 = "あのね、ヤンにそんなに否定的になるべきじゃないよ。実際、彼と和解したほうがずっといいんだ……結局、俺たちはみんな同じ目的を持ってるんだから！";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "「だが、お前を尊敬してるからだけだ……まあ、いいだろう。」 "+pchar.name+"、すみません。スヴェンソンを侮辱するつもりはなかったんです、ただ緊張していただけです。もう二度としません。";
			link.l1 = "よし。ダニー、すべてうまくいくさ。俺が約束するぜ！";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "「私はあなたを完全に信頼しています」 "+pchar.name+"……スヴェンソンのところへ行こうか？";
			link.l1 = "行くぞ、ダニー！";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "はい？聞いているよ。どうしたら力になれる？";
			link.l1 = "ジャックマンがどこに隠れているか心当たりはあるか？お前の方があの野郎のことをよく知ってるだろう。もしかして、 やつには隠れ家とか拠点があるんじゃないか…";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "俺にもさっぱり分からねえ！ジェイコブはいつもやたらと秘密主義だったからな。奴のアジトなんて聞いたこともねえよ。 論理的に考えたほうがいいかもしれねえ……ナイフからもらった手紙をもう一度読んでみようぜ。何か手がかりが見つかるかもしれねえ。";
			link.l1 = "やってみよう…";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "うーん……イスラ・テソロと何か遺言状について書いてあるな……心当たりはあるか？";
			link.l1 = "ヤンと俺は、ブレイズ・シャープはイスラ・テソロでジャックマンに殺されて、 その罪をシャークが着せられたと思ってるんだ。\nそれに遺言状…あの女…きっとヘレンのことに違いねえ…くそっ、なんで今まで気づかなかったんだ！この野郎、きっとイスラ・テソロの近くをうろついてやがる！";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "「それでは、時間を無駄にしないようにしよう」 "+pchar.name+"?";
			link.l1 = "ああ。イスラ・テソロへ行こう。古株の“マーリン”がこの襲撃を手伝ってくれるぜ。";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "あの野郎、ついにくたばったか……信じられねえ――また『センチュリオン』の甲板に立ってるとはな！ここの釘一本一本まで覚えてるぜ、 船もきっと俺のことを思い出してくれたんだろうな。";
			link.l1 = "「またお前のものだ、ダニー。お前とナサニエルのものだ。」";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "俺がどれほど嬉しいか、君には想像もつかないだろう。\nネイサンエルはよく俺たちの船のことを話していたんだ。また俺たちのものになったと知ったら、きっと喜ぶぜ。";
			link.l1 = "これからどうするつもりだ、ダニー？";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "俺か？俺は船をシャープタウンまで持っていって、最低限の乗組員を雇ってブルーヴェルドへ向かうつもりだ。 ヤン・スヴェンソンに『センチュリオン』の世話を頼んで、ミスキート族のところへ行き、 スネークアイが旦那を治してくれるまでそこで待つよ。";
			link.l1 = "本当にヤン・スヴェンソンに会いに行くのか？驚いたな……";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+"、全部あなたのおかげです。あなたの言葉――「みんな同じ目的を持っている」――について考えていました。覚えていますか？私はスヴェンソンと和解したいのです。結局、 彼はナサンを私のもとに戻してくれましたから。もう争いはやめる時です。";
			link.l1 = "さすがだな、ダニー！ネイサンは体調が良くなり次第、すぐにマルーンタウンで自分の地位を取り戻せるだろう。";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "もしかして……いや、実はな、海賊男爵ってのは選挙で決まる役職なんだ。他の連中が反対したらどうする？\n";
			link.l1 = "スヴェンソンに任せておけ。あいつなら誰でも説得できるさ。ジャックマンの排除も役に立つだろう。";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "仕方ない。どうせスヴェンソンと仲良くならなきゃいけないしな…… "+pchar.name+"！あなたとナサンのためにしてくださったすべてのことに感謝したいのです。あなたは私の夫を救い、 私たちが失ったすべてを取り戻してくれました。あなたには借りがあります。";
			link.l1 = "さあ、ダニー。俺たちは仲間だろう。";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "マルーンタウンではいつでもあなたを歓迎しますので、それを知っておいてほしい。\n時間ができたら、ぜひ私たちを訪ねてきてください。\nネイサンと私は、あなたに報いる方法を必ず見つけます。";
			link.l1 = "なんてことだ、ダニー！喜んでお招きにあずかるよ。座って、飲んで、 君とネイサンがどうやってヴァン・デル・デッケンを沈めたか語ろうじゃないか…";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "「彼が話したのか？ああ、そのことは思い出させないでくれ…」";
			link.l1 = "いいだろう、ダニー。お前にはこれからたくさん仕事が待ってるし、俺は誓いを立てた仲間――マーカスとバルバゾン――に会いに行かなくちゃならねえ。\nこの船室をひっくり返してもいいだろ？ジャックマンの宝箱には面白いものがたくさん入ってるはずだぜ。";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "もちろん、俺が反対すると思うのか？";
			link.l1 = "いいね。実は君と別れるのはちょっと寂しいよ、ダニー……またマルーンタウンで会おう！";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+"、お会いできて本当に嬉しいです！私たちはマルーンタウンに戻り、ネイサンも再び本来の場所にいます。実際、 村のみんなもそれを喜んでいます。これで、すべてが昔のようにうまくいくでしょう！ あなたの無私の助けに心から感謝しています！\nお礼に贈り物を差し上げたいです。どうぞ、受け取ってください。このお守りがあれば戦いがずっと楽になるはずですし、 この調合法があれば自分でももっと作れるようになりますよ。";
			link.l1 = "「ありがとう、ダニー！」";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "それだけじゃないんだ。ここで金貨がぎっしり詰まった宝箱を二つも見つけたんだよ。 間違いなくジャックマンの持ち物だったはずだ。俺の感謝の印として、これを受け取ってくれ。\n絶対に断るんじゃねえぞ！お前が俺とネイサンを助けるためにどれだけ金を使ったか、ちゃんと知ってるんだからな。";
			link.l1 = "わかった、わかったよ、ダニー、受け入れるぜ！";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "素晴らしい！ "+pchar.name+"、これからはあなたが俺たちの一番の友達だってことを知ってほしいんだ。 ネイサンと俺はいつでもマルーンタウンであんたに会えるのを楽しみにしてるぜ！もっと頻繁に遊びに来てくれよ！";
			link.l1 = "ありがとう！またお会いできるのを楽しみにしていますから、待っていてくださいね！";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "「俺たちに何か用か」 "+pchar.name+"?";
				link.l1 = "あいにく、ちょうど出発するところだ……さらばだ、ダニー。";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "「そして、これだ」 "+GetFullName(pchar)+"。顔を見れば、時間を無駄にしていないのがわかるぜ！";
					link.l1 = "正直に言うと、君は本当に楽しみ方を知っているな！ありがとう、素晴らしい時間を過ごせたよ。";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "お会いできて嬉しいです "+pchar.name+"「ラムか、ワインか？それとも女か？」";
			link.l1 = "ありがとう、ダニー！ただ君に会いたかっただけなんだ……";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "あの娘のことか？静かにしろ、ダニー！俺がバラバラにされて、 きれいに畳まれてお前の玄関先に置かれてるのを見たくないだろう？ははは。 ドアのすぐ外に立ってる俺の忠実なお嬢さんが、そんなふざけた真似をしたら絶対に許してくれねえんだよ。";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "女の子？それは面白そうだな、ダニー。俺はずっと…女の鼓動を求めていたんだ…ちょっと見に行くべきだな――お前が薦めるくらいだから、ただの女じゃねえんだろ？";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "本当か？なんでそんなに顔色が悪いんだ？はは、冗談だよ。彼女のこと、ちゃんと頼んだぜ、わかったか？";
			link.l1 = "もちろんだ。あの子はこの辺りのどんな財宝よりも俺にとって大切なんだぜ！";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "そっちの方がいいな、はは。さあ行けよ、お前の恋人がきっとそわそわしてるぜ。";
			link.l1 = "じゃあな、ダニー。心配してくれてありがとう、はは。";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "お約束しますよ、この若き美女は間違いなく忘れられないひとときを与えてくれますからね。 "+pchar.name+"。楽しんでくれ！彼女は酒場の部屋で待ってるぜ。";
			link.l1 = "ありがとう、Danny。今すぐ向かうよ。時間を無駄にしたくないんだ！";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+"、マルーンタウンではいつでも歓迎するぜ。最高の女たちはあんたのものだ！";
			link.l1 = "ああ、ダニー。誓って言うけど、ここは俺の第二の家だ。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "そして、私の船長が来たわ。今日はあなたは私だけのものよ！こっちにいらして、ずっとあなたを待っていたの…";
			link.l1 = "おや、そうなのかい？もう待てないって？よし、時間を無駄にしないで始めようぜ！";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("俺の船長……本当に女性の心を掴むのが上手いんだな！あんな体験、今までなかったぜ！もう少し、 あと二時間くらい一緒にいてくれないか？","「もうお帰りになるの、あなた？」");
			link.l1 = RandPhraseSimple("君がそんな簡単に俺を手放すはずがないって分かってたよ。じゃあね、ダーリン。俺には素晴らしい未来が待ってるんだ……","ああ、仕事が邪魔をしてしまう。しかし、また会えるかもしれませんね……");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "やっとネイサンと俺はまた自由に息ができるぜ！あの忌々しい野郎ジャックマンはくたばった！「センチュリオン」 のことは残念だが、あの野郎に奪われた時点でもう諦めてたからな。だからあまり気にしてねえよ。";
			link.l1 = "だが、俺は分かってる。俺はバカだ！証拠は全部、船と一緒に海の底に沈んじまったんだ。それがあれば、 コースト同盟の新しい頭領を選ぶ投票で役に立ったかもしれねえのに。\n今じゃ……全部なくなっちまった。";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "あまり気を落とさないで！こんなこともあるわ。次はもっと運が良くなるはずよ…まあ、とにかく、あなたが私とネイサンのためにしてくれたことに感謝したいの。あなたは夫の命を救ってくれたのよ。 本当に大きな借りができたわ。\nマルーンタウンはいつでもあなたを歓迎することを知っておいてほしいわ。時間があるときに、 私とネイトに会いに来てちょうだい。必ずお礼をさせてもらうから。";
			link.l1 = "わかったよ、ダニー。必ず会いに行くからな。もう行っちまうのか？";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "ああ、ムスキート族のところへ行くぜ。スネークアイがもうネイサンを治してくれてるといいんだがな。 そしたらマルーンタウンに戻るぜ。\n";
			link.l1 = "へへ、もうお前にはすっかり慣れちまったから、別れるのが惜しいぜ…元気でな、ダニー！";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "あら、とぼけないでよ、お嬢ちゃん。シャルル、この恋する小鳥はあのアイドルの周りを昼も夜もうろついて、 かわいそうなスネークアイにしつこく質問攻めしてたんだぜ。そんで、家に帰って何か持ってきてやったんだろ、 そうだよな？";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "ああ、見世物をありがとう、シャルル。マルーンタウン中が噂するだろうな、ははっ！";
			link.l1 = "それがあなたの新たな最優先事項になったことに疑いはありません――必ず実現させてください。";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "実は、俺の優先順位では一番下さ。あの娘を責めないでやってくれ――初めてなんだよ。ナサンと俺が冒険してた頃だって、諸島中のみんなに笑われてたもんさ。";
			link.l1 = "話題と気分を変えよう。この偶像にはもう用はない、行こうぜ。";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "同意だ、行こうぜ、英雄。";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "何の用だ、船長？";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "ダニー、君に相談したいことがあるんだ！";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "俺の命令を聞け！";
            Link.l1.go = "stay_follow";
			link.l2 = "たいしたことじゃない。下がれ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "ご命令は？";
            Link.l1 = "「ここに立て！」";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるなよ！";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "火器の弾薬の種類を変更する。";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選択：";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "態度が変わったぞ！";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "「進路変更だ！」";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
