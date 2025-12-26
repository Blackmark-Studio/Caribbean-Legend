// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
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
		case "First time":
			dialog.text = "何が必要なの？";
			link.l1 = "いや、なんでもないよ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "マルチェロ、あいつなら知ってるよ。リバドスや海賊たちの仲間だよ。アドルフがあいつと組むわけないでしょ？ねえ……火薬の匂いがしない？それに壁に血が……アドルフを殺して、今度は私たちを騙そうとしてるんだ！絶対に提督の手先だよ！あいつを殺して！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Cabin_fight");
		break;
		
		// на улице
		case "Town":
			dialog.text = "あっ、ごめんね……手伝ってくれる？";
			link.l1 = "ふむ。俺はいつだって美しい女性を助ける準備ができてるぜ。どうしたんだ？";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "見て、あたし、セシル・ギャラードから金属のかけらが詰まった箱を買ったの、でしょ？彼女はエヴァに住んでるの。 ユルゲンが何かいいものを鍛えてくれるって約束してくれたんだ、でしょ？あたしが買ったんだけど、 でも彼に持っていけないのよ。まったく、情けない！\nエヴァからエスメラルダのナーワルズ区画まで、その箱を運んでくれない？お願い、本当に感謝するから！";
			link.l1 = "「それだけでいいのか？もちろん、お嬢さん、手伝ってやるよ。問題ないさ。」";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "ありがとう！あたしが宝箱まで案内するね、でしょ？";
			link.l1 = "お嬢様…";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "そしてここに来た……さあ言え、この野郎、鍵はどこだ！？";
			link.l1 = "おったまげたぜ！はは、どうやら助けはいらないみたいだな……Mary。";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "生意気な奴だな？しゃべってないで、くそっ！鍵はどこだ？渡せよ、さもないと後悔させてやるぞ！";
			link.l1 = "失礼だな！こんなに美しい娘なのに、口が悪いんだな。鍵って何のことだ？";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "お前がアドルフ・バルビエから奪った鍵だ。\n言い逃れはするな、奴の船室から出てくるところを見られてたんだ。\nアドルフは死んだ、お前が殺したんだ……さあ、鍵を渡せ！";
			link.l1 = "やっぱりお前だったか……お前はやらかしたな、娘、でかい失敗だぞ！";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "何だと……？くそっ、お前はただの強盗じゃねえな！あいつは提督の手先だ！やっちまえ、野郎ども！\n";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "「Chad、あいつだ！くそっ、仲間を連れてきやがった！野郎ども、全員ぶっ殺せ！」";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "ちょうどいい時に来てくれたね…あたし一人じゃ絶対にあいつらに勝てなかったよ…ふう！正直、もう終わりだと思ってたんだ、でしょ？";
			link.l1 = "君はまるでワルキューレのように戦ったよ！こんなに美しい娘があんな激しく戦うのは見たことがない…";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "ははっ、紳士さんだね、剣を握ったまま褒め言葉なんて。助けてくれてありがとう。命を救ってくれたよ、でしょ？\n自己紹介してよ、旦那。あたし、あなたのこと見たことないよ。ここは初めてなの？";
			link.l1 = "私の名前は "+GetFullName(pchar)+"、でも美しい娘たちならあたしをこう呼んでいいよ "+pchar.name+"…あたしはここに来たばかりかって？ふむ…まあ、そうかもしれないね。";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "分かるよ。こんな素敵な男がいたら、私が気づかないはずないでしょ？私の名前はメアリー、メアリー・キャスパーよ。 みんな私のこと「赤毛のメアリー」って呼ぶの。だって私、赤毛でしょ？";
			link.l1 = "君に会えて嬉しいよ、Mary…";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "ああ、二重に嬉しいよ……あなたがいなければ、私はもう死んでたでしょ？あのクズのチャド、本気だったんだね。まったく、あいつは卑怯者だよ！ それに、下の扉を開けっぱなしにしてた私がバカだったんだ。あなたはそこから入ってきたんでしょ？";
			link.l1 = "うん。正義の島のまわりを泳いで、上陸できそうな場所を探してたんだ、でしょ？";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "なるほど。あの開いてた扉のせいで、もう少しで殺されるところだったよ。 ユルゲン本人が私のために錠前を作ってくれたんだ、正しい鍵がなきゃ開かないし、ピッキングも効かないよ。しかも、 誰かが中に入ろうとしたら、私だって黙ってないでしょ？ピストルの四連発で、扉でも体でも四つの穴が開くんだから、 ははっ！\nでも、あの忌々しいチャドが私を放っておかないんだ。手下を送り込んで私を『説得』しようとしたってことは、 本気ってことだよね、でしょ？もしあんたがいなかったら、私もイエスと言うしかなかった。 これからは包囲されてるみたいに、ここに籠もるしかないね。 "+pchar.name+"、でしょ！そのためにちゃんと準備しておいてよかったわ。物資はたっぷりあるし、ユルゲンは隣人だもの、 あたし彼と揉め事なんてないでしょ？";
			link.l1 = "Mary、どうして自分の悩みをちゃんと話してくれないんだ？あたしが助けを必要としてるのは分かるけど、 君の口から出たことは何ひとつ分からなかったよ。";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "ああ、助けが必要なんだ、でしょ？今は一人ぼっちなの。ドナルドと喧嘩しちゃって、 その後チャドが悪党だって分かって……ああ、ごめん、またおしゃべりが止まらなくなっちゃった。\nいいわ、私が今どんな状況にいるか話してあげる、でしょ？";
			link.l1 = "ここに来たばかりだから、まだあまりよく分かっていないんだ。\nその「説得」しようとしているか、殺そうとしているChadって誰？それに、Donaldって誰なの？";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "チャドはシャーク・ドッドソン提督の船団に属する海賊で、タルタロスの牢番だ…";
			link.l1 = "待って！シャーク・ドッドソンって言ったの？彼がここにいるの！？";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "今夜到着したばかりなんでしょ？だからそんなことも知らないんだよね、でしょ？シャークが他にどこにいるっていうの？ 私の災難は、あいつが数ヶ月前にここに来てから始まったんだ。でも、認めるけど、 全部ナーワルとリヴァドスのせいでもあるんだよ、でしょ？シャークが仲間を連れてここに来た時、 拠点を作ろうとしたんだけど、うちの人たちもリヴァドスもその考えが気に入らなかったの。 だから夜にシャークのブリッグを襲って火をつけたんだ。\n悪い考えだったよ！シャークの手下は人間じゃなくて悪魔だよ、でしょ？最初に奴らは私たちのボートを全部壊して、 それから上陸して私たちを殺し始めたの。ナーワルは撤退して、リヴァドスはできるだけ速く逃げ出した。最後には、 海賊たちが島の食料が一番集まってるサン・アウグスティンを占拠して、さらにタルタロスも奪ったの。\nシャークは私たちのリーダー、アラン・ミルローを捕まえて、しかも…私の…大切な人だったの、でしょ？それにリヴァドスの魔術師チミセットも。 あいつらを獣みたいにタルタロスの檻に閉じ込めたの。ここからタルタロスまでは泳いで行けるから、 私は何度かアランに会いに行ったんだ。そこでチャド・キャッパーに出会った。シャークが彼を看守に任命したの。 私はチャドにアランを解放してって頼んで、お金も約束したけど、彼は提督に逆らうのが怖かったんだよ、でしょ？\nそして、アランは牢屋で殺されたの。\nチャドが言ったんだ、シャークがやったって、でしょ？ だから私はアランの代わりにリーダーになったドナルドのところへ行って、すぐに海賊を攻撃しろって言ったの。 でも彼は断った。「あんな海の悪魔たちには勝てない」ってさ。だから私は「くたばれ」って言ってやったよ、でしょ？\n私の仲間は役立たずだったから、シャークの座を狙ってたクズ野郎キャッパーと取引したの。計画はこうよ――提督を砦からおびき出して、どこか怪しい場所で殺すの。それに、腕のいいライフル持ちの狙撃手も見つけた。 フューリー号のマストから提督を撃てるって話だったの。\nで、面白いのはね、おとといの夜にタルタロスに行って、チャドに計画の大事なことを伝えようとしたの。 泳いで船に近づいたら、チャドがナーワルの二人と話してるのを聞いちゃった。 実はアランを殺したのはシャークじゃなかった。チャドだったの。チャドが提督のせいだって噂を流したんだよ、でしょ？ \nチャドがアランを殺したのは私のせい――まずは私をベッドの玩具にするため、次に私を使ってシャークを始末するため。 チャドは私が復讐を諦めないって分かってたんだよ、でしょ？信じられる？最低のクズだよ！";
			link.l1 = "ああ、あいつみたいな奴には会ったことあるよ…";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "クソ野郎の方がもっとひどいよ！あいつは…あたし、あの化け物を言葉で表せないよ、でしょ？泳いで逃げた後、翌朝あいつを見つけて、 思ってること全部ぶちまけてやったんだ。そう、あたしは提督への陰謀には絶対に加担しないって言ってやったの、 でしょ？";
			link.l1 = "そして彼は当然それが気に入らなかった……無鉄砲だったよ、Mary。もっと用心すべきだったんじゃないか。";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "分かってるけど、黙ってなんかいられなかったんだよ。あの野郎、アランを殺して、 自分の都合のためにあたしを利用しようとしたんだ！クズめ！でしょ？それで、もちろん怒って「後悔させてやる」 って言ってきたの。あたしは「そのタマ切り落としてカニに食わせてやる！」って言い返したよ！\nもし考えを変えなきゃ仲間をけしかけるって脅してきたけど、あたしは笑ってやった。 ナーワルの奴があたしに手を出すなんて、思いもしなかったからね。";
			link.l1 = "勘違いだったみたいね。";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "「ああ、」 "+pchar.name+"、私はChadを侮って、自分を過信していた。彼は、ひとりきりの女の子を自分の船室で襲うような悪党どもを見つけてきたんだ。 これからどうすればいい？誰も信じられない、自分の仲間すら信じられない。今殺したこの二人もナーワルズの連中だ。 二人ともよく知ってた、でしょ？Chadが生きている限り、私は危険なままだよ。やつはきっと、また手下を送り込んでくる、間違いない。\nドアの外に出るのも怖い。Sharkを暗殺するために雇った狙撃手が、Rivadosの領地から私を撃って、逃げてしまうかもしれない。Donaldのところへは行かない――あの人は話なんて聞いてくれない。\nそれに提督？「お願いです、旦那、暗殺計画に加担したのは認めますが、どうかお許しをいただいて、 昔の仲間から私を助けてくれませんか？」\nあの人なら、私をタルタロスの牢屋で腐らせるか、頭に鉛玉をぶち込むか、どっちかだよ。くそっ、袋小路だ！ 食料が尽きるまで銃を構えてここに座ってるしかない、でしょ？その後は……もう、わからない！";
			link.l1 = "そういうことなら、助けるしかないでしょ？あんたの状況、ここでのあたしの計画にも合ってるし…";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "あたしを助けたいの？でもどうやって？チャドを殺すつもりなの、でしょ？";
			link.l1 = "それも作戦のうち、でしょ？";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "「聞いて、」 "+pchar.name+"、気持ちはありがたいけど、あんたには荷が重すぎるよ。チャドは提督の親友の一人だし、たとえ会えたとしても、 生きては帰れないよ。シャークの海賊たちがあんたを殺す。奴らは真実なんて知らないんだ、でしょ？";
			link.l1 = "落ち着いて。どうせサメと話さなきゃならないんだ。";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "じゃあ、あんたも海賊なの！？さあ、話してもらうよ。カッコつけて私の部屋に押し入って、命まで救ってくれて、 助けるって約束までしたのに、あんたのこと何も知らないんだよ、でしょ！？";
			link.l1 = "……わかったよ。あたしは海賊じゃないけど、今はある海賊男爵――ヤン・スヴェンソンと一緒に働いてるの、でしょ？ここに来たのはナサニエル・ホークを探すため。彼のこと、 聞いたことある、でしょ？";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "いいえ、誰それ？";
			link.l1 = "また有名な海賊だね。彼に会ったことがないなんて残念、でしょ？きっとこの辺にいるはずよ。 あたしもシャークを探してたんだけど、まさかここで見つけるとは思わなかった、でしょ？";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "でも、どうやってここに来たの？遭難者にしては元気そうでしょ？";
			link.l1 = "「どうしてあたしが難破したって決めつけるの、でしょ？」";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "ここに来る方法はそれしかないんだよ。シャークだけがここまで航海したことがあるんだ、でしょ？";
			link.l1 = "「まあ、見ての通り、シャークだけじゃないでしょ？」";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "じゃあ、船を手に入れたの？すごいじゃない、でしょ！";
			link.l1 = "あまり興奮するなよ、Mary。俺は……バーク船でここに来たんだ。バーク船で来たけど、沈んじまったんだよ、海の底にな。\n";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "あ、ああ……まあ、言ったでしょ？難破したのよ。今はあんたも私たちとここに閉じ込められてるんだ、でしょ？";
			link.l1 = "Mary、俺の計画を話すよ。君はChadがSharkを殺すつもりだって言ってたよな、でしょ？俺はSharkに生きていてほしいんだ。俺とJanで彼を海賊たちの頭に据えるつもりだよ。だからこそ、彼に警告しなきゃならない。君の話からして、Chadは君の協力があろうとなかろうと必ず実行するって確信してるからさ。";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "ああ、たぶんね。あいつにはそれを実現できるだけの手下がいるから…";
			link.l1 = "つまり、俺の第一の目的はシャークの信頼を勝ち取って彼を救うことだ。それから、正式にチャドに取りかかるつもりだ。 \n彼の有罪を証明する証拠は持っているか？";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "この手紙を持っているんだよ、ここにいる床に転がってる…このバカどもの一人が運んできたやつさ。中には脅しやら細かいことが書いてあって、提督が興味を持ちそうな内容だよ。 \n待って！あたしはどうなるの？シャークに、チャドと組んでたのがバレちゃうでしょ？";
			link.l1 = "Mary、いつまでここでピストルを抱えて、みんなからその可愛い顔を隠しているつもりなんだ？ 本当に俺が美しい女の子の死を背負いたいと思ってるとでも？まずは手紙を見せてくれ、何ができるか見てみよう…";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "ほら。どう思う、でしょ？";
			link.l1 = "ちょっと待って……（読みながら）。うん、チャドはこの世に蔓延る特別なクズ野郎の一人みたいだね、でしょ？この手紙があれば、 シャークは自分からチャドの首に縄をかけたくなるはずだよ。心配しないで、奥方、 シャークには絶対にあなたのことがバレないようにするから。どうせシャークはチャドのことで手一杯になるしね。";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "本当にやってくれるの？約束して、でしょ！絶対にあたしを裏切らないって誓って！";
			link.l1 = "メアリー、君に誓うよ、絶対に裏切らない。君を助けたのは、死なせるためじゃないんだ、でしょ？\nチャドは君を放っておかないさ、間違いなくね。君は知りすぎている。あいつが死ぬまで、ここにいてくれ。";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "ああ、ここに残るよ。狙撃手に撃たれたり、背中を刺されたりなんてごめんだからな。";
			link.l1 = "いい子だね。全部の扉を閉めて、下の扉も忘れずに。鍵はあなただけが持っているのかい？";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "違うよ。もう一つあるんだ。欲しい、でしょ？";
			link.l1 = "うん。あたしのこと信じてる、でしょ？";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "そうね、今命を救ってくれた素敵な旦那に裏切られたら、生きてる意味なんてなくなっちゃうよ……受け取って、でしょ？";
			link.l1 = "怖がるなよ、美人さん！俺は君をがっかりさせたりしないぜ。この騒ぎを片付けたらすぐに会いに行くからな。 きっと時間はかからないさ。";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "大丈夫、ここは数週間くらいならあたしが守れるでしょ？";
			link.l1 = "いいね。じゃあ、時間を無駄にしないよ。まず死体を運び出してからシャークと話す、でしょ？ 彼はサン・アウグスティンにいるんだよね？";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "ああ、彼はいつもそこにいるよ。\nそれから、ここに入ってきたのと同じ方法で出ていって。セレス号の上甲板には絶対に足を踏み入れさせないから、 でしょ？";
			link.l1 = "それはどうして、でしょ？";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "あなたが死んだら、私を助けることなんてできないでしょ？\nここはイッカクの縄張りで、よそ者は殺されるんだから、でしょ？";
			link.l1 = "ふむ……わかったよ。じゃあ、Mary、またな。安全になったらすぐ戻るからな。";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "あたしに会いたい時はいつでも来ていいよ、全然かまわないから、でしょ？（くすくす）";
			link.l1 = "さらばだ、美しい人よ！";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "「こんにちは」 "+pchar.name+"でしょ？何かいい知らせはある？あんた、大丈夫でしょ？";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "シャーク・ドッドソンとの争いは解決したよ。もう君を追い回すつもりはないんだ。\n今や彼が気にしているのはチャドの裏切りだけ、でしょ？";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "まだだよ、Mary。でもあたしにできることは全部やるつもり、でしょ？";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "ああ、神様ありがとう！助けてくれて感謝するよ、忘れないからね、でしょ！ 少なくとも提督のことは心配しなくて済むわ。で、チャドは？シャークは何をしたの、でしょ？";
			link.l1 = "俺たちはリバドスをそいつの後を追わせるよう説得した。レイトン・デクスターはタルタロスから衛兵を引き上げて、 牢屋の鍵をブラック・エディに渡した。黒人たちは自分たちの魔術師チミセットを解放したが、 チャドを殺すことには失敗した。チャドのナーワル仲間二人はやられたが、チャド自身は逃げてどこかに隠れている。";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "くそっ！つまり、今まで以上に気をつけなきゃいけないってことだな！";
			link.l1 = "落ち着け、Mary。きっとあいつはお前よりSharkのことを気にしてるはずだ。誰がRivadosをけしかけたかもわかってるんじゃないか。あいつはSharkを殺すためなら何でもするさ、お前じゃなくてな。";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "当てにしないで。チャドはそんなに簡単に諦める男じゃないよ。ああ、彼に怯えて生きるのはもううんざりだ…";
			link.l1 = "ふむ。あんたが簡単に怖がるような女だとは思わなかったよ。";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "はっ！ちゃんと戦うのは怖くないけど、尻を敷いて殺されるのを待つなんて？それはすごく怖いよ。 "+pchar.name+"、でしょ！…";
			link.l1 = "信じてくれ、Mary。Kapperは提督のことで手一杯なんだ。今は…君の助言が必要なんだ、でしょ？";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "私の助言？どんな助言のこと、でしょ？";
			link.l1 = "エディがチャドの書いた手紙を二通見つけたよ。読んでみて、もしかしたら彼が何を企んでいるかわかるかもしれない。 君は結局チャドと一緒に計画に加わっていたんだろう……";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "渡して……（読む）アクセルはエスメラルダ号の商人だね、でしょ？チャドが彼からウイスキーを買いたがってた？変だな。 チャドはラムしか飲まないよ、ウイスキーなんて「百姓の密造酒」だって言ってたのに……";
			link.l1 = "「それで、二通目の手紙はどうするの？」";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "「マルチェロ」？マルチェロ・サイクロプス、元王室の狩人よ。あいつがいるから、私はこの船室から出たくないの、 でしょ？";
			link.l1 = "あいつがあなたが雇った狙撃手でしょ？";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "ああ。片目を失っていても、マルチェロは四十フィート先のハエだって撃ち抜けるんだ、でしょ？彼の任務は、 サンタ・フロレンティナのバウスプリットかフューリーの見張り台から、 長距離用シュトゥッツェンでシャークを狙撃することだったの…";
			link.l1 = "つまり、あいつはまだチャドのシャーク殺しの計画の一部ってわけか。\nでも……エヴァ？セシル？酒？";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "エヴァ号は中立の船で、セシルはセシル・アラール、船に住んでいる面白いおばあさんだよ。 彼女は最近サンタ・フロレンティナからここに引っ越してきたんだ。オレリー・ベルティーヌは彼女の友達で、 二人ともあたしが生まれる前から正義の島にいるんだ、でしょ？";
			link.l1 = "ふん。ばかばかしいな。大の男二人が年寄りの女から隠れて一緒にウイスキーの樽を飲むなんて？くだらない……チャドが酒を飲むには、妙な時と場所だな。\n";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "あたし言ったでしょ？彼はウイスキーは飲まない、ラムだけだって……なんかおかしいよね、でしょ？";
			link.l1 = "よし、まずはキュクロプスから始めよう。彼の居場所、知ってるでしょ？";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "いいえ。彼はとても秘密主義なの。毎日外輪で鳥を撃ってるけど、誰も彼がどこで寝てるか知らないのよ。 よくリバドスのところに行くの、でしょ？";
			link.l1 = "手がかりはあまりないな……まあ、じゃあアクセルに話をしに行くよ。もしかしたら彼なら何かわかるかもしれない。じゃあな、Mary！戸締まりしっかりしておけよ！";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"、早くChadを見つけて、でしょ？前回の襲撃以来、あたし一睡もしてないんだから。";
			link.l1 = "しっかりつかまって、ダーリン。あたし、できる限り頑張るから、でしょ？";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"「！どうやってここに来たの？彼は来たの、もしかして――？」";
			link.l1 = "ああ、君を殺すためだよ、Mary。Jurgenの船室を通ってここに来て、ロープを使ってここまで降りてきたんだ。";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "ああ！あたしって本当にバカだよ！その道のこと、すっかり忘れてた！チャドが彼に話したんだ、でしょ？絶対そうだよ！ ";
			link.l1 = "たぶんね。あたしもギリギリだったよ、でしょ？";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "あたし、寝てたんだよ。あいつ、あと一秒であたしを殺してた…でも、どうしてあいつがここに向かってるってわかったの、でしょ？";
			link.l1 = "ああ……あたしにはあたしのやり方があるのよ、Mary。";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "また助けてくれたね、イケメン。いつも絶妙なタイミングで現れるんだから、でしょ？どうやってるの？";
			link.l1 = "そうね、わからないな。あたしのたくさんある才能のひとつ、でしょ？\n包囲戦は終わったよ――チャド・キャッパーは死んだし、仲間も全員お陀仏。サイクロプスがあいつら腐った連中の最後だったんだ、でしょ？";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "本当に、 "+pchar.name+"？あたしをからかってるんじゃない、でしょ？";
			link.l1 = "全然だよ。ええっと、この数日間の後はちょっと休みが必要でしょ？";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "やっと自由に息ができるようになった！ありがとう…本当にありがとう！あんたはあたしのヒーローだよ、でしょ？";
			link.l1 = "その響き、好きだよ―あたしがあんたのヒーローになるってやつ、でしょ？やっと無事でいてくれて、本当に嬉しいよ。";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "でしょ？";
			link.l1 = "どうしたんだい、可愛い子？";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "なんでそこに突っ立ってるの？こっちに来なよ、旦那。";
			link.l1 = "「それで何をするの、でしょ？」";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "こっちに来て、あたしを抱きしめて、キスしてよ。欲しいんでしょ？わかるよ、でしょ？";
			link.l1 = "「メアリー……」";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "あたしを置いていかないで……";
			link.l1 = "ああ、ここにいるよ、メアリー、愛しい人…";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "全部待たせていいのよ。あなたの提督も、あなたの海賊たちも、みんな待たせて。この夜はあたしたち二人だけのもの、 でしょ？";
			link.l1 = "そう、でしょ？";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "「そして、その後のすべての夜も……」";
			link.l1 = "「そうだよ、メアリー。」";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"！戻ってきたんだ…彼女なしで。つまり、彼女はあなたを私から奪えなかった、でしょ？";
				link.l1 = "メアリー、君の疑いは根拠がなかったよ。あたしにとって君だけなんだ。いつも心でも夢の中でも君と一緒だった、 でしょ？";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+"、なんでイッカクたちと戦ってるの？あたしはあの子たちの縄張りに住んでるし、忘れたの？ あたしもイッカクの一員なんだよ。お願い、ファジオのところに行って仲直りしてきて、頼むよ。";
				link.l1 = "わかったよ、Mary、君の頼み通りにするよ。";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+"、何か悩んでるんでしょ？どうしたの？";
				link.l1 = "メアリー、君と話がしたいんだ。";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"！ナーワルたちみんながあんたの噂をしてるよ！";
				link.l1 = "本当に、あなた、でしょ？";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"！このブロードソード、すごいね！ありがとう！あたしもお礼にプレゼントをあげたいの。もちろん、 あなたのものには敵わないけど、受け取ってほしいんだ、でしょ？";
				link.l1 = "メアリー、君からの贈り物なら何でも大切にするよ……ありがとう、愛しい人。";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "「今日は忙しくなりそうだね、でしょ？」 "+pchar.name+"？幸運を祈るよ！";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "メアリー、今日ユルゲンに会いに行かないといけないよ。";
					link.l3.go = "narval";
				}
				link.l1 = "ありがとう、Mary！それは全く疑ってないよ。";
				link.l1.go = "exit";
				link.l2 = "今日はやめておくよ、Mary。ここで少し休みたいんだ。それでいいかい、でしょ？";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "「さて、」 "+pchar.name+"、元気してる？いつも通り島を駆け回ってるの、でしょ？";
				link.l1 = "ああ、Mary。やるべきことがたくさんあるな……";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = ""+pchar.name+"、もう夕方だよ、何の話してるの？ここにいて、一緒に飲んでゆっくりしよう、でしょ？ 他のことは朝まで待てばいいんだから！";
				link.l1 = "（笑いながら）もちろんよ、愛しい人、もう言わなくていいでしょ？";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "メアリー、今日は酒場に行こうぜ！";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "メアリー、愛しい人よ、今はとても忙しいんだ。少ししたら戻るからね。";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "夕方には必ず会いに来てよ。絶対にあたしを避けたりしないで、でしょ？";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "メアリー、今日はユルゲンに会いに行かないといけないんだよ。";
					link.l3.go = "narval";
				}
				link.l1 = "もちろんだよ、Mary、どうしてそんなことできるんだ？絶対に会いに来るよ。";
				link.l1.go = "exit";
				link.l2 = "メアリー、今夜はここで休みたいんだ。君はそれでいい、でしょ？";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "何言ってるの？もう夜だよ！どこにも行かせない、ここにいて、あたしと一緒に、でしょ？";
			link.l1 = "（笑いながら）あんたの願いはあたしの命令よ、でしょ？";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "やめてよ……";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("「素晴らしい考えだね、でしょ？」 "+pchar.name+"、でしょ！あたしも賛成だよ！","ああ、行こうぜ、 "+pchar.name+"！サンチョは素晴らしいワインのコレクションを持っているんだ、選び放題だよ！","ああ、喜んで行くよ、でしょ？サンチョの酒場はいつも楽しいし、あそこはワインの品揃えも最高なんだよ！");
			link.l1 = "行こう！";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "「もちろん」 "+pchar.name+"、どれくらいここにいるつもりなの？";
			link.l1 = "昼までここにいるよ……";
			link.l1.go = "rest_day";
			link.l2 = "夕方までここにいるよ……";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "「もちろん」 "+pchar.name+"、どれくらい滞在するつもりなの？";
			link.l1 = "夕方までここにいるよ……";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"！帰ってきたんだね……あの子はいない。つまり、あの子はあなたを私から奪えなかったってこと、でしょ？";
				link.l1 = "メアリー、君の疑いは根拠がなかったよ。あたしにとっては君だけ、でしょ？ いつも心でも夢の中でも君と一緒だったんだよ、でしょ？";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+"、なんでイッカクたちと戦ってるの？あたしはあの子たちの縄張りに住んでるし、あたし自身もイッカクの一員なんだよ、 でしょ？忘れたの？お願い、ファジオのところに行って仲直りしてきて、頼むよ。";
				link.l1 = "わかったよ、Mary、君の頼み通りにするよ。";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"！このブロードソード、すごいよ！ありがとう！あたしもお礼をしたいんだ。もちろん、 あなたのには全然かなわないけど、受け取ってほしいの、でしょ？";
				link.l1 = "メアリー、君からもらうものなら何でも宝物だよ……ありがとう、愛しい人。";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "もう行っちゃうの、でしょ？ "+pchar.name+"？幸運を祈ってるよ、でしょ？あたしのこと、忘れないでね……";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "メアリー、今日はユルゲンに会いに行こう、でしょ？";
					link.l3.go = "narval";
				}
				link.l1 = "ありがとう、Mary！";
				link.l1.go = "exit";
				link.l2 = "メアリー、ここで少し休みたいんだ。君はそれでいい、でしょ？";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "ククルカンのところに行かないの、でしょ？ "+pchar.name+"?";
				link.l1 = "まだだよ、まだ準備中でしょ？";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "もう夕方だね、 "+pchar.name+"……ここにいてくれない？あたし、あなたと一緒にいたいんだよ、でしょ？";
				link.l1 = "わかったわ、あなた、あたしはここに残るよ…";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "メアリー、今日は酒場に行こう！";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "幸運を祈ってるよ、そしてあたしのこと忘れないで…できたら夜に会いに来て、でしょ！";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "メアリー、今日はユルゲンに会いに行こう、でしょ？";
					link.l3.go = "narval";
				}
				link.l1 = "わかったわ、あなた。";
				link.l1.go = "exit";
				link.l2 = "メアリー、ここで少し休みたいんだ。君はそれでいい、でしょ？";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "何言ってるの？今は夜だよ！だめ、どこにも行かせない、ここにいてもらうから、でしょ！";
			link.l1 = "（笑いながら）でしょ？あたし、ここに残るよ…";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Captain "+pchar.name+"！士官メアリー・キャスパーがあなたの指揮下で仕える準備ができてるよ！";
				link.l1 = "よくやったぞ、士官！俺はお前にすぐ船に乗り込むよう命じる。だがその前に……船長にキスしろ！";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "すごかったよ、あなた……おはよう！";
				link.l1 = "おはよう、あなた！最高だよ！";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "ドナルドと話したの？提督がリバドスと同盟を結んでナーワルと戦おうとしたって本当？ それをあなたが思いとどまらせたって本当なの？海賊とナーワルの間に平和が訪れるの？\n";
			link.l1 = "そうだよ、メアリー。まさにその通りだね。";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+"…言葉が出ないよ…それに、ドナルドもあなたのことを友達だと思ってるってさ。あなたもナーワルズの一員になれるかも、でしょ！";
			link.l1 = "時間があるときにドナルドに会って、でしょ？彼もあなたと和解したいって。\nチャドから守れなかったことや、きついことを言ったことを許してほしいって頼んでたよ、でしょ？";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "ドナルドなんてくたばっちまえ！でも…それを聞いて嬉しいよ、もちろん。彼には会うつもり。でも、あんたは！あたし…あんたのこと誇りに思ってる、でしょ？";
			link.l1 = "おお、神よ、Mary、君は……ああ、君のせいで胸が高鳴るよ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "話そうよ！困ってるの、でしょ？";
			link.l1 = "違うよ。メアリー……最初に会った夜を覚えてるか？あの二人の野郎を片付けた後、俺が船でここに来たって話しただろう。";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "覚えてるよ、でしょ？お前のバーク船は沈められて、ここまで泳いで来たんだよね…でしょ？";
			link.l1 = "嘘をついたの。あの時本当のことを言ったら、私が狂ってるって思ったでしょ？\nバルク船なんてなかったのよ。\nスペイン領の本土でインディアンの神様ククルカンの魔法の偶像を使って、ここに来たんだ、でしょ？";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"…何のことを言ってるの？ククルカン？";
			link.l1 = "メアリー、お願いだ、信じてくれ。理屈じゃ説明できないし、あなただけにしか話せないんだ、でしょ？ ネイサン・ホークはインディアンの偶像に触れて姿を消したんだ。追われていて、それが彼をここに送り込んだんだ……";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "...";
			link.l1 = "ナサニエルを探していたんだ。\nインディアンのシャーマンに話をして、ホークと同じように偶像に触れた。\nそしたら、サン・アウグスティン号の船倉の中に転送されて、船体の穴から外に出たんだ…そして運命があんたのもとへ導いてくれたんだよ。";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "これって、いつか子供たちに語る面白い話になるってこと？それとも、あんた本気で気が狂ったの、でしょ？";
			link.l1 = "怒ってなんかいないよ、Mary！信じるのが難しいのは分かってる――君には狂ってるように思えるかもしれないけど……お願いだ、あたしを信じてくれ。";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "エリックの話は本当だったみたいね……";
			link.l1 = "エリックって誰？どんな話なの、でしょ？";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "エリックはこの島の住人の一人で、昔の船乗りだったの。今はもうとっくに亡くなってるけど、あたしが子供の頃、 彼がよく話してくれたのは、インディアンの偶像や、 リバドス族がこの正義の島で人間を生け贄に捧げた祭壇の話だったわ。\nそれに触れた者は……消えて……二度と姿を見せなかったって。子供を怖がらせるための作り話だと思ってたの、でしょ？";
			link.l1 = "本当だよ、Mary。Ericは嘘をついてなかったんだ。";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "幸いにも、あの恐ろしい偶像を積んだ船は沈んだんだ。あたし、自分の目で見たことはないけど、でしょ？";
			link.l1 = "見つけたよ、海底で休んでたんだ、でしょ？";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "あそこに潜ったの！？あの忌々しい発明家ヴェデッカーがスーツを貸してくれたの？ あそこにはカニがうようよいるんだよ、でしょ！？あいつめ！あんたをそんな危険に晒して、許せないよ！";
			link.l1 = "メアリー、俺のことは心配しなくていい。カニなんて自分でどうにかできるさ。みんなが言うほど怖いもんじゃない。 俺はこの島に来た初日からずっと像を探していて、ついに見つけたんだ。";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "「それで、これからどうなるの、でしょ？」";
			link.l1 = "この偶像だけがここから出る唯一の方法だ。俺は海底にあるのと同じ偶像を通ってこの島に来たんだ、 そしてまたそれを使って戻るつもりだ……メアリー！泣いてるのか？ああ、メアリー、頼む、泣かないで……";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "なんで泣いちゃいけないの？泣きたい時は泣くよ、でしょ…（すすり泣き）こういうこと、私の仲間にはいつも起こるんだよ！また一人ぼっちになっちゃうじゃない、でしょ！？";
			link.l1 = "私がどうなると思う？あたしがあんたをここに置いて行くなんて、本気で思ってるの！？あたしは必ず戻ってくるよ、 船に乗って。あんたも、それに\n "+sTemp+"ネイサンエルは私と一緒に戻ってきた。私と一緒に外の世界へ行く？";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "（涙ながらに）もちろん……もちろん、あたしは待ってるよ……絶対に戻ってきてくれる、でしょ？どうやって正義の島に戻るつもりなの？ここに来れるのはシャークだけだよ――それに、あたしのこと忘れたりしたら許さないからね、見つけたらぶん殴るから、でしょ！？";
			link.l1 = "メアリー、もういい加減にしてくれ！もちろん君を迎えに戻るさ！君と出会ってから、 俺の心をこんなに高鳴らせる奴なんて他にいないだろ？心配するな、愛しい人よ。 シャークが正義の島への座標と行き方を教えてくれた。必ずまた君を見つけ出す。";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "スペイン領本土の偶像があんたをここに送ったって言ったけど、もし下の奴があんたを別の場所――たとえばアフリカとかに連れて行ったらどうするの？その時、あたしはどうすればいいの、でしょ？！";
			link.l1 = "ククルカンはインディアンの神様だ。俺をカリブ海かスペイン領本土のどこかへ連れて行くつもりだろう。\nあとは集落を見つければいい。そうすれば自分の船と乗組員を見つけるのは簡単だ。";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "（泣きながら）約束して…いや、誓って、必ず戻ってくるって、でしょ？！";
			link.l1 = "メアリー、愛しい人よ、君に誓う、必ず戻ってくる。\nそして君をこの惨めな場所から連れ出すよ。\n寂しがるのはもう少しだけでいい。\nもう涙はやめてくれ。";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "「いいよ」 "+pchar.name+"……戻ってきてよ、あたし待ってるから、でしょ！いつ出発するの？";
			link.l1 = "まだわからないよ。まず自分の準備をしないと、それから潜って像に触れるつもり。\n私が溺れたって言われても、信じないで、でしょ？\nきっと全部うまくいくから。";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "分かったよ。 "+pchar.name+"…ねえ、抱きしめて…キスして…";
			link.l1 = "メアリー……ああ、愛しいメアリー……";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "ユルゲン？どうして？";
			link.l1 = "見てて。これはきっと嬉しい驚きになるよ、でしょ？";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "あら、面白いじゃない！楽しいの？でしょ？さあ、行こうよ、好奇心で死んじゃう前に！";
			link.l1 = "きっと気に入るよ、でしょ？行こう！";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "行こう、 "+pchar.name+"!";
			link.l1 = "……でしょ？";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "「さて、」 "+pchar.name+"、どんな驚きを用意してくれたの、でしょ？";
			link.l1 = "Mary！ユルゲンと私で、君にプレゼントを贈ることにしたんだ、でしょ？\nこれは特別な剣、「ナーワル」の名を持つブロードソードだよ。世界にこの剣は二振りしかないの。 最初の一本はアラン・ミルローが持っていた。そして、もう一本は君のもの、でしょ？\n特別な鉄で作られていて、ユルゲンの匠の技で鍛えられているから、決して切れ味が鈍ったり錆びたりしないんだよ。";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "愛しい娘よ……ナーワル一族のみんなは、お前がどれほど苦しんできたか知っている。 お前にはこのナーワル一族の象徴であるブロードソードを持つ資格がある。誇りを持って身につけなさい。 この剣はお前の敵にとって恐怖となり、戦いでお前をしっかり守ってくれるだろう。";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "ユルゲン？これ…あたしにくれるの…でしょ？…";
			link.l1 = "うん、Mary。 "+sld.name+"  君のために作ってくれって頼まれて、海の底から特別な鉄を持ってきてくれたんだ。\nこの素材の重さと強さに勝る鋼なんてないよ。\nアランの時と同じように、この剣にも魂を込めたんだ。";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "何て言えばいいのか分からないよ……ありがとう、Jurgen、ありがとう！誇りを持って身につけるし、それにふさわしい自分になるって誓うよ、でしょ？ ブロードソードでの訓練はあまりしてないけど、これからはやるよ！";
			link.l1 = "疑いなんてないさ、お嬢ちゃん。";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"…待って…あんたは今まで会った中で一番素敵な男よ！本当にすごいんだから、でしょ？これが私にとってどれだけ大事なことか、 わかる？この剣は今までで一番の贈り物よ！もう何度も私を助けてくれて、命まで救ってくれたのに、 まだ私を驚かせてくれるんだもん！ありがとう、私の愛しい人！";
			link.l1 = "これは君にふさわしいよ、Mary。俺は最後の息まで、毎日君を驚かせ続けるからな！\n君の笑顔を見ると本当に幸せになるし、贈り物を気に入ってくれて嬉しいよ。";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "（くすくす）ありがとう！なんて素敵な剣なんだ、でしょ？これを振るうには強い腕が必要だよ…早くこれで訓練を始めたいな！";
			link.l1 = "すぐに習得できると思うよ、でしょ？急いで自分の船室に行って、試してみて！";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "それをやるつもりだよ。改めてありがとう、旦那！ "+pchar.name+"…今夜、準備ができたらあたしに会いに来て…（くすくす）、でしょ？";
			link.l1 = "もちろんです、お嬢様。夕方にお会いしましょう。";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "ほら、見てみて。外輪の船のひとつで見つけたの、船長の宝箱の中にあったんだよ。経験豊富な船乗りはみんな、 このお守りは航海士にとってものすごく価値があるって言うの。最悪の嵐から船を守ってくれるんだって。 欲しがる人はたくさんいたけど、あたしは売らなかった…あなたに持っていてほしかったの、ダーリン。これを使って、海の上でも無事でいてね。";
			link.l1 = "ありがとう、Mary！本当に気が利くね、愛してるよ！";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "本当に？気に入ってくれたの？ああ、嬉しい！すごく嬉しいよ、でしょ？";
			link.l1 = "これはとても珍しくて貴重なお守りだよ。もちろん気に入ったよ！ありがとう、あなた！";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"…戻ってきたんだね。毎日水平線を見つめて、あなたを待ってたんだよ、でしょ？あたしのところに帰ってきてくれた…";
			link.l1 = "うん、Mary。約束通り来たよ。抱きしめさせてくれ、愛しい人！";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "「あっ、」 "+pchar.name+"…想像もできないでしょ！？ナーワルズは、あなたが溺れ死んだって言ってたの。みんな、 あなたが死んだって信じて疑わなかった。あたしはずっと「生きてる」って言い続けてたのに…もちろん、誰も信じてくれなかったよ。みんな、あたしが色々あって頭がおかしくなったと思ってたんだ。";
			link.l1 = "メアリー……愛しい人よ！どうしたんだ？震えてる……寒いのか？";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "ううん、寒くなんかないよ。ただ……ここで話したくないだけ。後であたしの船室に来て、でしょ？あんたと二人きりで話したいの。 今から提督とナサニエルに会いに行くの？";
			link.l1 = "うん。シャークと話さなきゃいけないし、もちろんダニエルをナサニエルのところに連れて行かないといけない。 すぐ戻るよ。すぐ会おう、メアリー。";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "あたし…あたし、会えるのを楽しみにしてるよ。できるだけ早く来て、でしょ？";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"！やっとだね。話さなきゃ、でしょ！";
			link.l1 = "どうしたんだ、Mary？何か悩んでるみたいだな。何があったんだ？";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "彼女は偶然…… "+pchar.name+"「おい、あんたの船にいるあの売女は誰だ？」";
			link.l1 = "娼婦？ダニエルのことを言ってるの？でも、もうあんたは知って――";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "違う、ダニエルじゃないよ。あたしが言ってるのは、あんたの船の甲板をうろうろしてる、あの半裸の金髪女よ！ 望遠鏡でちゃんと見たんだから、でしょ！？";
			link.l1 = "あ、あれはヘレン・マッカーサーよ。彼女もダニエルと同じく、この奇妙な話に関わってるの、でしょ？ 今は一時的に私の士官をやってくれてるのよ、もちろん一時的にだけど。";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "士官？彼女があんたの士官なの！？";
			link.l1 = "まあ、そうだよ。でしょ？それの何が悪いの？Mary……くそ、あんた、嫉妬してるんだね！";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "当然でしょ？！…（涙を浮かべて）ずっとあんたを待ってたんだから。あんたのせいで眠れなかったのに、戻ってきたと思ったら、 あんな尻軽女と一緒なんて――";
			link.l1 = "メアリー！泣くのはやめろ！どうしたんだ？お前はためらいもなく男を刺し殺せるくせに、 いつも目が濡れてるじゃないか……メアリー、いいかい、ヘレンはただの士官だよ。俺たちの共通の目的が果たされるまで一時的に仕えているだけで、 それ以上の意味はないんだ。";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I've been training hard with the broadsword you gave me, and I've mastered it perfectly!";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I've been training hard with rapiers and I've mastered them perfectly.";
			dialog.text = "（すすり泣き）士官……じゃあ、あたしもあなたの士官になりたい、でしょ？あたし、戦えるんだから、知ってるでしょ！ "+sTemp+" それに、あたしは射撃が得意なんだよ！海の技術はまだないけど、覚えるのは早いんだから。あたし、才能あるでしょ？";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "（同意）Mary…君にその役職を自分から頼もうと思ってたんだ。君ほど情熱的で腕の立つ娘はいないよ！俺のそばにいてほしいんだ！";
			link.l1.go = "adversary_hire";
			link.l2 = "（拒否）メアリー！斬り込み士官なんて危険すぎる！君は自分が何を頼んでいるのか分かっていないんだ。 君の命を危険にさらすわけにはいかない。";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "できないの？あの金髪の売女は士官になれるのに、あたしはダメってこと？嘘ついてる、でしょ？ "+pchar.name+"、あたしと一緒にいたくないんでしょ！？（泣）あの子の方があたしよりいいってわけ、でしょ？";
			link.l1 = "メアリー、君にはわからないんだ！";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "あたしもそう思うよ！あの子があなたを見るとき、目が輝いてたもん、でしょ？彼女はただの士官じゃないんだよ、 でしょ？それは分かってる。（すすり泣き）もちろん、あたしじゃ敵わないよ――彼女は船の操り方を知ってるもん…";
			link.l1 = "メアリー、何を言ってるの？";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "終わりよ……（泣きながら）あっち行って！あんたの娼婦のところへ帰りなさいよ！あたしはここに残るから……！鍵を返して、でしょ！？";
			link.l1 = "でも、Mary…";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "どこかへ行って…";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "本当に？私を本気で自分の士官にしたかったの、でしょ？ "+pchar.name+"くそっ、どれだけ嬉しいか想像もできないでしょ！？あたし、あなたの士官になりたくてたまらないんだよ…でも、あの金髪と同じ船は絶対に嫌だからね！";
				link.l1 = "メアリー、でもどうして！？";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "本当に？あたしを本気で自分の士官にしたかったの、でしょ？ "+pchar.name+"くそっ、あんたには想像もできないくらい嬉しいんだから！誓うよ、絶対にあんたを裏切らない、見ててよ！";
				link.l1 = "イエス、マリア、可愛い人、君は本当に大切な存在だよ。さっきまで泣いていたのに、 今は顔がぱっと明るくなってるじゃないか！それに、メアリー、君は俺にとってただの士官じゃないんだ。 もっと特別な存在だし、君が俺を裏切るなんて絶対に思えないよ。";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "あんたは彼女のことをただの部下としか見てないかもしれないけど、彼女はあんたをただの船長だなんて思ってない、 でしょ？\nあたし、彼女があんたに向けた視線を見たよ。その目つき、よく知ってるんだ、でしょ？\nでも、あんたにそんな目を向けていいのは、あたしだけなんだから。";
			link.l1 = "メアリー、愛しい人よ、前にも言っただろ、俺はあの女に気持ちなんてないんだ、それだけだ！俺たちの間には何もない！ 誓うよ、くそっ！ブレザレン・オブ・ザ・コーストの厄介ごとを片付けるために、彼女の助けが必要なんだ。 俺が彼女を助けなければ、ヤン・スヴェンソンはトルトゥーガ攻略に協力してくれないし、俺には彼が必要なんだ！";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+"…ねえ、抱きしめて…ごめんね。あたし、あなたを信じてるよ。でも、あの子のそばにいて、 あなたに色目を使うのを黙って見てるなんてできない、でしょ！そのうち、あたし、 剣を抜いてあの子を真っ二つにしちゃうから！";
			link.l1 = "あんたならやると思ってたよ…本当に気が強いんだね、でしょ？";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "もしあの子を殺してしまったら――君は私のもとを去るでしょ…それだけは、絶対に自分を許せないよ。";
			link.l1 = "それで、どうしたらいいと思う、Mary？あの子をどうすればいいんだ、でしょ？";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "「彼女は臨時の士官だって言ってたよね。君が彼女を上陸させたら、できれば誰もいない無人島に置いてきたら、 すぐにでも一緒に行くから、でしょ？（くすくす）地の果てまでもついていくよ、でしょ！\nそれで、教えてよ、」 "+pchar.name+" ねえ……あの子、本当にあたしよりいいの、でしょ？";
			link.l1 = "馬鹿なこと言うなよ！そんなこと言うのはやめろ、Mary、君より素晴らしい女なんていないんだ…";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "じゃあ、証明してよ。あんたを誰にも渡さない、でしょ？ "+pchar.name+"！他の誰かと君を分け合うくらいなら、君を手放す方がマシだよ、でしょ？";
			link.l1 = "わかったよ、Mary。取引しよう。今はHelenを手放せないんだ――俺の冒険には彼女が不可欠だからな。彼女の問題を手伝って、Isla Tesoroの女王にしてやったら、彼女を自由にする。そうすれば、俺とお前を隔てるものは何もなくなるはずだ。うまくいけば、 一、二か月もかからないと思う。そんなに待ってくれるか？";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "やるよ、でしょ！はっきり言うけど……もしあんたが私のところに戻ってきたら、それは彼女じゃなくて私を選んだってことだよ。\nでも戻ってこなかったら……それで終わり。私はここに残って、自分の一族――カスパー一族を作るんだから！";
			link.l1 = "また泣いてるのかい？Mary、もうやめなよ、でしょ？「自分の一族を見つけた」って……お前は本当におかしな娘だよ、でしょ？もちろん戻ってくるさ！ こんなボロ船だらけの中にお前を置いていけるわけないだろ！お前の涙で正義の島が水浸しになっちまうよ！";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "できるだけ早く戻ってきてね、でしょ？ "+pchar.name+"…キスして、お願い…";
			link.l1 = "必ず戻るよ。約束する、でしょ！"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = ""+pchar.name+"、あたしのために戻ってきてくれたの、でしょ？";
			link.l1 = "もちろん！あたしがあなたに嘘をついたことなんてある？あなたと離れているなんて耐えられないし、 もう二度と離れるつもりなんてないよ…あたしの愛しい人、でしょ？";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "本当に？ "+pchar.name+"！どこへでもついていくよ！絶対に嘘なんてつかない、絶対に裏切らない、誓うよ！";
			link.l1 = "信じてるよ、あなた…あたしも絶対に裏切らない、でしょ？"; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+"、ねえ、抱きしめて…あたしたち一緒にいるよね、でしょ？約束して！";
			link.l1 = "ああ、俺たちは一緒にいるよ、Mary。永遠に。";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "ダニエルやナサニエルと同じように、でしょ？";
			link.l1 = "（笑いながら）そう、まさにあの人たちみたいでしょ？";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"…あんたのこと、大好きよ！もしプロポーズされたら、たぶん結婚しちゃう、でしょ？…";
			link.l1 = "親愛なるMary…もちろん、この話は後でしよう。君の船の墓場での人生はもう終わりだ。ここから連れ出してあげる。\n俺の船へようこそ…そして広い世界へ、愛しい人よ！";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "この島で最後の夜を一緒に過ごそう、セレス号で。二人きりでね。朝が来るまで、あなたをどこにも行かせないから、 でしょ。";
			link.l1 = "まあ、今は私たち、あなたの船にいるんだよね、私のじゃなくて……だから、あたしはあなたの命令に従うよ、Casper船長。";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "了解だ、旦那！";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"！いい考えがある…";
			link.l1 = ""+npchar.name+"ここは安全じゃないよ。あたし、君には船に残るよう命じたでしょ――";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+"くそっ、どこも安全じゃないじゃないか！このオンボロ船には島ごと吹き飛ばせるくらい火薬が積んであるんだぜ！ よく聞けよ、でしょ？";
			link.l1 = "聞いてるけど、手短にしてくれ。";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "海賊のコルベットとフリゲートだ。奴らはまだ私たちを仲間だと思ってる……あのナイフ野郎、でしょ？それなら火薬樽をいくつかと導火線を持って、フリゲートで出航しよう。\n横付けしたら導火線に火をつけて、樽を投げ込んで、できるだけ速く離れるの。 奴らのケツを木っ端みじんに吹き飛ばしてから、コルベットに乗り込むんだよ。";
			link.l1 = "危険だね……でも……あなたの作戦、うまくいくかもしれない、でしょ？でも、あいつらを十分近づくまで騙せたらの話だよ。";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "あたしはやってみようって思うんだ、でしょ？ "+pchar.name+"";
			link.l1 = "よし、やってみよう。\n野郎ども！火薬樽を三つ持ってこい！\nははっ、あんたの考え方、大好きだよ。 "+npchar.name+"！こんなこと、自分じゃ絶対に思いつかなかったよ。";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "お礼はあとでいいよ…（ウインク）";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "命令通りに報告します、旦那！（くすくす）どうしたの？";
			link.l1 = "ジャックマンの船はサボ・マティラ入り江に停泊している。重フリゲート艦センチュリオンだ。 この船はかつてホークス家の所有物だったから、船長室には重要な品や書類があるはず……乗り込まなければならない。";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "ちくしょう……どうやってあの小鳥でやるつもりなの？望遠鏡で覗いてみたけど、センチュリオンにはどれだけ人と大砲がいるか、 ちゃんと見たんだから、でしょ！";
			link.l1 = "その通りだ。ジャックマンの手勢は俺たちの倍はいるし、全員が腕利きの殺し屋や傭兵だ。 まず数を減らさずに乗り込むなんて正気の沙汰じゃない。しかもセンチュリオンの大砲の口径じゃ、長引く海戦も無理だ。 どうすればいいのか、わからない……";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+"まだ私たちを敵だと認識してないよね、でしょ？トルクスの馬鹿どもみたいにさ。 もう一度火薬のトリックを使えるんじゃない？";
			link.l1 = "メアリー、今言ったばかりだよ、フリゲートに乗り込むんだ、沈めるんじゃないって！";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "知ってるよ、でしょ？ "+pchar.name+"！沈めはしないよ。空のラム酒樽をいくつか用意して、火薬とブドウ弾、それに短い導火線を詰めるんだ。 それからセンチュリオン号の横につけて、その爆弾を甲板に投げ込むぞ。";
			link.l1 = "はっ！本当にうまくいくと思ってるの、でしょ？";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "なぜ駄目なんだ？あいつらの舷側はうちより高いが、二、 三人いれば滑車を使って満載の樽を簡単に持ち上げて投げ込めるさ。\n「悪党からの無料ラムだぞ！」って叫ぶんだ。相手が反応する前に樽が爆発するってわけだ。";
			link.l1 = "炸裂ブドウ弾で甲板の連中をみんなバラバラにしちまう……くそ、そそられるじゃねえか。";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "「五つの樽を使ってくれ、」 "+pchar.name+"……奇襲の利があるんだ。奴らは何も疑わないはず！でも爆弾を投げた後はすぐに離脱しないと、乗り込まれちまうからな。 爆発したら、今度はこちらが戻って乗り込むぞ。";
			link.l1 = "奴らに樽を投げ込む前に、俺たちの正体を悟られちゃいけねえ…くそ、近づくのは簡単じゃなさそうだ。ジャックマンはグールみたいな馬鹿じゃねえからな。";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "だから、一番効き目のあるお守りを持っておいたほうがいいよ、 "+pchar.name+"。赤毛のMaryを信じて、でしょ？やってみる価値はあるよ。";
			link.l1 = "いいところ突いたね、俺たちには失うものなんてない……でしょ？導火線の準備、君がやってみない？";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "了解だよ、船長！あたしに任せて、でしょ？";
			link.l1 = "メアリー、君は素晴らしいよ！";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "「ありがとう」 "+pchar.name+"！絶対にあなたをがっかりさせないよ、でしょ？";
			link.l1 = "あんたが裏切らないのは分かってるよ、でしょ？でも、 あたしたちがあんたの計画を台無しにしてがっかりさせないようにしないと…武器を取れ！";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "やっと見つけた！探すのにちょっと苦労したよ…でも、すごかったね、船長！あんな見事な跳躍、初めて見たよ！まるで英雄みたい、でしょ？でも正直、 心臓が止まるかと思ったよ。いつかあなたのそういう芸当で、あたし死んじゃうかもね、ねえ…\nで、あの女は一体誰なの？ちょっと目を離しただけで、もうどこかの尻軽女を見つけてきたってわけ？";
			link.l1 = "メアリー！この「くず」はキャサリン・フォックス、シー・フォックス団の司令官フォックス大佐の娘だ。 彼女をアンティグアへ連れて行かなくちゃいけないんだ。";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "あら、本当？それは嬉しいわ。いいわよ、彼女のことを話してくれても……今夜、私たちの船室で。あたしと二人きりでね。さあ、行こう、急がなきゃ！";
			link.l1 = "（はぁ）君がいなかったら俺はどうなってたんだ、Mary？Catherine、行くぞ！";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "ああ神様、目を覚ましたのね！この野郎！もう二度とそんなふうにあたしを驚かせないでよ、でしょ！？";
			link.l1 = "メアリー……愛しい人、どうしたんだ？頭が……ううっ……";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "船長のキャビンに入ったとき、あなたは死体のように床に横たわっていたんだよ。 俺たちはあなたを拾い上げて自分たちの船まで引きずっていった――ちょうどその時、甲板に転がっていた骸骨たちがまた立ち上がり始めたんだ、でしょ？\n 神よ、本当に恐ろしかった！俺たちにはどうすることもできなかったんだ！綱を切って逃げようとしたけど、 あいつらの砲撃で船がひどく損傷して操縦不能になった。まさに悪魔どもだったよ、でしょ？ それからあいつらは帆を上げて、一瞬で地平線の彼方に消えちまった。\n 俺たちの船は座礁しちまったから、嵐で壊される前にロングボートでこの浜辺まで来たんだ。 今日はたくさんの仲間が死んだけど、船はなんとか……ギリギリで生き残ったよ。";
			link.l1 = "よくやったな、Mary…。お前がいなかったら俺はどうなってたんだろうな？";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "そうね…もしかして溺れた？あの船に閉じ込められた？死者たちに引き裂かれた？くそっ…そしてあんたもくたばれ、でしょ？ "+pchar.name+"、そんなに怖がらせてくれて！";
			link.l1 = "静かに、Mary、静かに。助けてくれてありがとう、愛しい人。どれくらい気を失っていたんだ？";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "一日だよ。あんたの傷を手当てして、薬も飲ませて、ラム酒もちょっと飲ませたんだから。すぐ元気になるはず、でしょ？ あたしの前で死ぬなんて許さないからね！";
			link.l1 = "約束するよ、愛しい人。だけど……もっと元気だった時もあるんだ、でしょ？";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "今までの君はもっと元気そうだったけど……彼女のせいか、 "+pchar.name+"「フライング・ダッチマン」だったの？そんな話は聞いたことあるけど、まさか本当に……\nどうしてあいつらは私たちを追い詰めたの？それに、乗り込む前にどうして砲撃しなかったの？";
			link.l1 = "奴らの船長はあの護符を欲しがってたんだ、私がトゥットゥアタパク――インディアンのシャーマン――と話したやつね。それで私たちの船に乗り込んできたけど、船長が護符を手に入れた途端、 もう私たちを無傷で残す必要はなくなったのよ…\nなんて悪夢なの！死人が操る船だなんて、信じられない…カリブで最悪のものはもう見たと思ってたのに。";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "やっぱり「フライング・ダッチマン」が君を迎えに来るのは時間の問題だったんだね、でしょ？\nくそっ、あれには本当にビビって、また教会に行きたくなっちゃったよ！";
			link.l1 = "あんたの気持ち、わかるよ。あたしもあのインディアンの村に戻って、トゥットゥアタパクに何があったか伝えなきゃ、 でしょ？あの船が私たちを襲ったのはアミュレットのせいだよ！あの赤い肌の悪魔が、 なんであの生ける屍どもが最初にそれを欲しがったのか、ちゃんと説明してくれるといいんだけど、でしょ？";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "わかった、でも気をつけてね。まだボロボロなんだから、でしょ？";
			link.l1 = "あんたがいれば他に薬なんていらないよ。で……メアリー、あたし、あんたのことが好きなんだ……";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "あたしもあなたのこと愛してるよ、ダーリン……生きてて本当によかった、でしょ！？";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+"あなたの腕の中にいることほど幸せなことはないよ、でしょ？……さあ、行こう！",""+pchar.name+"もしできるなら、あたしは目が覚めてる間ずっとあなたと一緒にいたいよ、でしょ？さあ、行こう！");
			link.l1 = RandPhraseSimple("あなたは最高よ、私の愛しい人…","あなたは素晴らしいよ、私の愛しい人…");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("んん、あなたって本当にすごいよ……いつだって、でしょ？","最高だったね！");
			link.l1 = RandPhraseSimple("あなたを喜ばせることができて嬉しいよ、愛しい人…","あいしてるよ、Mary…");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+"あんたの腕の中にいたいって本気で思ってるんだよ、でしょ？\nでも今はそんな場合じゃないよ――あのクズ野郎ティボーを逃がす前に捕まえなきゃ。";
				link.l1 = "いつも君の言う通りだよ、あたしの娘よ…";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+"あなたの腕の中にいるときほど幸せなことはないよ、でしょ？…さあ、行こう！",""+pchar.name+"もしできることなら、あたしはずっとあなたのそばにいるよ、でしょ？さあ、行こう！");
			link.l1 = RandPhraseSimple("あんたは最高だよ、あたしの娘…","君は素晴らしいよ、俺の情熱的な赤毛の美女……");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+"……もうずいぶん長いこと、あたしたち体を重ねてないよね……すっかりあたしのこと忘れちゃったんでしょ？でしょ？今夜は部屋を取って、悩みごとは明日に回そうよ。",""+pchar.name+"、あたしのことすっかり忘れちゃったんじゃないかって思い始めてるよ！ねえ、あなたと…二人きりの時間が欲しいの、でしょ？今夜は部屋を取ろうよ、でしょ？",""+pchar.name+"どこに行ってたの？あたし、あなたと一晩過ごして、ワインを飲んで、ゆっくりしたくてたまらないんだよ、でしょ？ ずっと海にいて、あたしのことなんてすっかり忘れてたんじゃない！？");
			link.l1 = "メアリー、愛しい人、何を言ってるんだい、「私のことなんてすっかり忘れてた」なんて。おバカさんだな……でも本当に忙しすぎて、俺の手を離せない問題が山ほどあるんだ。許してくれ、愛しい人よ。さあ、上に行こう。 今夜は全部君のものだ。世界なんて待たせておけばいい！";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("今日は無理よ、でしょ？やることが山ほどあるんだから。","メアリー、可愛い人、どうして君のことを忘れるなんて思うんだい？あとで一緒に過ごそう、でしょ？ 今はやるべき仕事があるんだ。"),RandPhraseSimple("メアリー、君のことはいつも考えているよ。でも今は気を抜いている場合じゃないんだ。","Mary "+npchar.lastname+"、今日はこんなことにかまっている暇はないんだ。"));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "（はぁ）しょうがないわね、じゃあ自分の船室で一人遊びでもしてるよ…でしょ？はい、船長。";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "「チャールズ…」";
			link.l1 = "メアリー、愛しい人、何を言ってるんだい、「私のことなんてすっかり忘れてた」だなんて。お馬鹿さんだな……でも本当に忙しすぎたんだ。俺の手を離せない問題が山ほどあってさ。許してくれ、愛しい人よ。さあ、上に行こう。 今夜は君だけのものだ。世界のことなんて後回しでいいさ！";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "あっ、いた！もうあたしのこと好きじゃなくなったんでしょ？教えてよ！";
			link.l1 = "「何だって！？Mary、これは一体どういうふざけた話なんだ？どうしてそんなふうに思うんだ？」";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "じゃあ、なんであんた、あの売春婦たち、娼館の女たちのところに通ってたの？あたし、知ってるんだから、 嘘つかないでよ！あたしと愛し合ってるとき、何か気に入らないことでもあるの、でしょ？（泣きながら）教えてよ……";
			link.l1 = "Mary、Mary……落ち着いてくれ、お願いだ、娘よ。確かに何度か娼館に行ったことはあるが、全部仕事の用事だったんだ。 楽しもうなんて思ってなかったんだよ！";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "「それで、二階の寝室でどんな“ビジネス”があったの？（すすり泣き）嘘ついてる、でしょ？」 "+pchar.name+"!";
			link.l1 = "メアリー、お願いだからやめてくれ…本当に娼館の女主人と仕事の話があったんだ。\nそれに、確かに何度か二階にも行ったけど、最後は総督の個人的な用事だったんだよ。 結婚指輪を探してくれって頼まれてさ。閣下の頼みを断れるわけないだろ？";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "...";
			link.l1 = "それでどうやって女主人に「二階のベッドの下を調べたい」なんて説明できると思う？無理だよ。だから仕方なく、 一晩だけ娼婦を買って二階に上がる許可をもらったんだ…\n二度目は、商人がそこで船の書類をなくしたって聞かされた。また女を買って部屋を探す羽目になった――でも実際に書類を見つけて、しかもかなりの報酬をもらったんだよ…";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "...";
			link.l1 = "そして三度目は地元の司令官を手伝っていたんだ。駐屯地の将校について娼婦たちに聞き込みをしなきゃならなかった。 その将校はスパイ容疑と海賊との内通を疑われていたんだ。結局そいつを捕まえて、俺は立派な報酬をもらったんだよ…";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "...";
			link.l1 = "わかったでしょ？言ったじゃないか、全部仕事だったんだよ。メアリー、あたしが愛して必要としてるのは君だけだ。 君に誓う、浮気なんてしない！\n君がいるのに、あんな汚い港の娼婦と寝るなんて、できるわけないでしょ？どうしてそんなこと考えられるの！？";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = "…それは今まで聞いた中で一番のたわごとだよ、でしょ？でも… "+pchar.name+"…本当のことを言ってるの？あたしの知らないところで他の女と寝てない、でしょ？";
			link.l1 = "メアリー、愛しい人よ、違うよ、誓って何もしてない。あなただけを愛してるんだ、本当だよ。こっちにおいで、 愛しい人。抱きしめさせて……涙を拭いて、お願いだから、もう嫉妬しないでくれ！君が望むなら、俺はもう二度と娼館なんか見向きもしないよ！";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "ああ、それがあたしの望みだよ… "+pchar.name+"…あたし、嫉妬しちゃうんだよ…だってあんたのこと愛してるから、失いたくないんだもん、でしょ？ もしあのクズ女があんたにちょっとでも笑いかけたら、次に彼女の中に入るのはあたしの剣だからね！";
			link.l1 = "イエス、マリア、落ち着いてくれ……誰も殺す必要なんてないんだ！あたしは君を失ったりしない、約束するよ。大丈夫、落ち着いて。 君は俺のたった一人の女で――しかも世界一素敵な人なんだ！信じてくれ。";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+"、なんて変な質問なの？あたし、あなたのこと愛してるよ。あなたがあたしを救ってくれたんだよ。 あたしがあなたを一人で行かせると思う？そんなこと考えないで、でしょ！あたしも一緒に行くよ！いつ出発する？";
			link.l1 = "そうだね、あなた。どうして疑ったりできるのかしら、でしょ？\n行くときはちゃんと教えるから。まずはしっかり準備しないとね、でしょ？";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "準備できてるよ、 "+pchar.name+"……あんたについて地獄の果てまででもついていくよ！";
			link.l1 = "ありがとう、愛しい人…";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.MarySexBlock = "true"; // fix 22-03-20
			dialog.text = "今度は何が来たの、船長？スペイン人？海賊？それとももっと悪い奴ら？";
			link.l1 = "もっとひどいんだよ、Mary、ずっとひどい。総督が悪名高い高級娼婦のところへ訪問するつもりで、俺は「興味深い人物」 として付き添わなきゃならないんだ。\n退屈な話、法外な値段のワイン、つまらない貴族たち、ってわけさ。";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "まったく逆さ、貴族のご婦人が主催する社交の催しへの招待状よ。閣下が私に同行を頼んできたときは驚いたけど、 正直言って、ちょっとした気晴らしを楽しみにしているの。";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "おおっと！確かにもっとひどいな！高級娼婦！強いワイン！社交！でしょ？まるで純粋な拷問みたいだよね、 "+pchar.name+"、このクソ――";
			link.l1 = "メアリー、落ち着いてくれよ。俺がそこに行くって言っても…娼館に行くわけじゃないんだ！いや…まあ、娼館には違いないけど、俺は紳士だし約束は守る男だ、でしょ？これまで一緒にやってきたのに、 あたしのこと本当に信じてないのか？総督からちょっとした頼みごとをされたから、それを果たすだけなんだよ、 それだけさ！";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "ああ、そういう「貴族様」たちのことは聞いたことあるよ、でしょ？あんたの連れにも見かけたことあるし。 あいつらにとっちゃ、愛人稼業が日常茶飯事なんだよ。『上流』社会だの、『品格ある』娯楽だの、笑わせないでよ！ 結婚したって、こういう……うぇ……「ご婦人方」のところに通うのはやめないんだから。あんたにはもっと期待してたのに、でしょ？ "+pchar.name+"。まあね、あんたら「貴族」なんて、あたしの洗ってない尻の穴でも舐めてな、でしょ？";
			link.l1 = "メアリー、待ってくれ！くそっ…";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "あたしたち、二人とも休暇をもらう権利あるでしょ？へへ、赤いコートを着た女を見て、みんな耐えられるかな？ 隅っこでひそひそ話が絶えないよ、でしょ？誰かきっと気絶しちゃうよ――それって面白いよね、でしょ？";
			link.l1 = "メアリー、愛しい人よ、ここは淑女を連れてくるような場所じゃないんだ……少なくとも、君みたいな淑女にはね。ちょっと複雑なんだけど、説明させてくれ――";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "あたしみたいな女？はっきり言うけど、あんなカツラ野郎たちには釣り合わないよ。あたしは単純すぎて、身分も低い、 でしょ？華やかな宴会にも、立派な旦那シャルル・ド・モールにも、ふさわしくないんだよ、でしょ？";
			link.l1 = "いや、全然そんなことないよ。君は本当に素晴らしいし、周りの人たちにどう思われようが気にしない。 総督はいつも通り、私の助けで自分の問題を解決しようとしてるんだ。 私は彼にとって貴重な戦利品みたいなものになるだろうし、 貴族の役立たずどもを感心させるための面白い客になるだけよ。\n";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "いや、 "+pchar.name+"「……いいよ、わかってるって。貴族は貴族同士で、下々は外にいろってことね。（ぺこり）心からお楽しみくださいませ、 クソ貴族様。あんたがまた庶民の土を踏んだ時にでも話しかけるわ、でしょ？」\n";
			link.l1 = "メアリー、待ってくれ！ああ、くそっ…";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "心から願ってるよ、社交的な時間を楽しんでね、アスホール旦那。\n謙虚な土の上に戻ったら、また話そうか。";
			link.l1 = "メアリー、もう、やめてよ！";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "見てよ、でしょ？うちの上流社会で迷子になった船長さんだよ！";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "一日中売春宿に消えてたら、町中がその話でもちきりよ。チャールズ、 私がナーワル号をあんたの尻に突っ込まないでおく理由を一つだけ教えて、でしょ？";
			link.l1 = "メアリー、全部説明するよ、でも後でね。今は決闘の準備をしなきゃいけないんだ――もし生き残ったら好きに殺してくれて構わないよ。\nその間、新しい船のことを頼むよ、でしょ？昨夜カードゲームで勝ち取ったばかりの賞品なんだ。";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "船なんてどうでもいい、決闘って何だよ？\n地元の連中の話を聞くと、お前は王の息子かローマ教皇と戦うことになってるみたいじゃねえか。\n一体何が起きてるんだ、教えてくれよ！";
			link.l1 = "この男は非常に影響力のある貴族、ルヴィ・ヴァンタデュール伯爵の私生児なんだ。\n挑んできたのは彼の方で、俺は彼を傷つけずに決闘に勝たなきゃならない――父親の怒りを買わないためにな。";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "あんたが今勝ち取ったオンボロ船で、俺は尻でも敷いて座ってろってか。正気かよ、チャールズ？";
			link.l1 = "こうするしかないんだ、でしょ？総督が私に立会人として貴族の士官を二人つけてくれたの。 後で誤解が生じないようにね。\n決闘の公式な公正さを守るために、あたしはあなたや乗組員の誰も連れていけないんだよ、でしょ？ これはあまりにも重大なことなの、ごめんね。";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "…今から何をするかわかる？あの忌々しい船に乗り込んで、思いっきり酔っぱらってやるんだ。\n好きにしなよ。でも一つだけ正しいことがある——あの貴族のろくでなしがあんたを殺し損ねたら、あたしが自分でやるからね。";
			link.l1 = "メアリー、大丈夫だよ、信じて。今は待って……くそっ！また始まったぞ！";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "いたいた！今日は一言も聞かせてくれなかったじゃない！\n市場で噂を聞いて、心配になったんだから。船や女を賭けてギャンブルしてたとか、王子様か、 はたまた法王とまで決闘したって話まで出てるよ！\n一体何がどうなってるの！？";
			link.l1 = "複雑なんだよ、Mary。説明するにはちょっと時間がかかるんだ。でも、フリゲート艦を手に入れることには成功したんだ、でしょ？ 俺が前の持ち主との揉め事を片付けている間、その船の面倒を見てくれよ。";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "じゃあ、決闘ってこと！？前の持ち主は誰なの？なんでそいつと戦うの、でしょ？";
			link.l1 = "ややこしい話だけど、要するにね、あたしは彼の船と…女を勝ち取ったの、でしょ？彼は公の場であたしをイカサマ呼ばわりして、決闘を申し込んできたの。 あの男はすごく権力のある貴族、ルヴィ・ヴァンタデュール伯爵の私生児なんだよ、でしょ？あたしは彼を傷つけずに、 どうにかしてこの決闘に勝たなきゃいけないんだ。";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "噂は本当だったの？船を賭けるのは分かるけど……女まで賭けるなんて、本気でしょ？";
			link.l1 = "くそっ、Mary、全然違うんだよ！あいつは総督から彼女を勝ち取ったけど、俺はあいつから彼女を取り戻して解放しただけなんだ、 それだけだ。ほかには何もない、誓うよ！";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "まあ、貴族のあんたにはこれが普通かもしれないけど、あたしには全然違うんだよ、でしょ！好きにすればいい、 好きなこと言えばいい……彼女のために死にたきゃ勝手に死ねば？あたしはね、あんたが勝ち取ったクソみたいな船に行って、 屋根裏部屋をラムでめちゃくちゃにしたいんだよ。くたばれ、 "+pchar.name+"、あたしたちの間にあったものは本物で、ずっと…ずっと続くって信じてたよ、でしょ？期待しすぎちゃったみたい！";
			link.l1 = "メアリー、あの女なんて俺はどうでもいいんだ！ちょっと待ってくれ、頼む…くそっ！またかよ…";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "チャールズ、迎えに来てくれたんだね！やっぱりそうだと思ってた、全然疑わなかったよ、でしょ？会えて本当に嬉しい！ ";
			link.l1 = "あたしもよ、Mary！この一件、ずっと胸が苦しかった…でも無事で本当によかった、でしょ！？";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "ところで、どうやってあんなに簡単に私を解放させたの？ちゃんとした乱闘も銃撃戦もなかったのに、でしょ？\nそれと、甲板で私が引きずり出されるときに、あの女の人を見かけたよ。何があったの、Charles？";
			}
			else
			{
				dialog.text = "一体何をしたの？どうしてあんなにあっさり私を解放してくれたの？戦いもなければ、銃声もなし、 何もなかったじゃない！私が連れ出されたとき、甲板にイギリスのきざな連中がいたのを見たよ。 あれは一体どういうこと、チャールズ？";
			}
			link.l1 = "大事なのは、君がまた俺のもとに戻ってきてくれたことだけだ。俺は君を守れなかった、Mary。本当にすまない！どうか、君の心で俺を許してくれることを願ってる。俺たちの間があんなふうになってしまったのが、 たまらなく嫌なんだ。";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "もう済んだことだよ。あたしもごめん、でしょ？あんたとあの女のこと、つい個人的に受け止めすぎた…あの夜、ちゃんと見張りを立てておくべきだったのに――あんな簡単にやられるなんて！あたし、ほんとバカだったよ！";
			link.l1 = "過去は過去だよ。あたしはあなたを愛してるし、もう二度とあんなふうにあなたを置いていったりしない、でしょ？ 約束する！";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "疑ってごめんね、チャールズ。もしかして…あなたが何をしたのか、正確には知らない方がいいのかも、でしょ？また一緒にいられる、それだけで十分だよ。";
			link.l1 = "あたし、あなたに隠し事なんてないよ。全部話すね…";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "なんて話だろうね……他の誰も信じてくれないだろうな、でしょ！？やっぱり！あんたの“社交”の夜は絶対に怪しいと思ってたんだよ！あの貴族のクジャクども……冷たい奴らばっかり！でも、あんたのことだけは間違ってなかった——あんたは他の奴らと違うって、わかってたんだよ、でしょ！？";
				link.l1 = "外の多くの人たちは、あたしのことをもっとずっと悪い存在だと思ってるはずだよ、でしょ？ おとぎ話に出てくる本物の怪物みたいにね。";
			}
			else
			{
				dialog.text = "なんて話なの……他の誰も信じてくれないと思うよ、でしょ？やっぱりね！あんたの“社交”の夜がただの遊びじゃないって、あたし分かってたんだよ！政治に、スパイに、陰謀に――それでもまた、あんたがみんなを救ってくれた、でしょ？あたしのヒーローだよ。";
				link.l1 = "それはどうかな……数週間以内にイギリスとの戦争が始まる可能性が高いんだ。でも、やるべきことはやったよ、Mary。君は俺にとってすべてなんだ。";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "人がどう思おうと関係ないよ。そういうことなら、チャールズ、あんたはあたしの怪物でしょ？ みんなが気に入らないなら、あたしが話してやるよ。あたしはいつだってあんたのそばにいるから、でしょ！";
			}
			else
			{
				dialog.text = "分かってるよ、Charles。ずっと前から知ってた…でも、あなたの口から聞けて嬉しいよ。あたしもずっとあなたのそばにいるから、でしょ！";
			}
			link.l1 = "疑ったことなんて一度もないさ、Mary。行こうぜ、みんな心配してる。今こそ帆を上げて、ここから脱出する時だ。お前がまた俺のそばにいるし、 あの地平線が俺たちを待ってる……";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "あいよ、船長！";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "チャールズ、本当にあなたなの？あたし、もうほとんど希望を失いかけてたんだよ、でしょ！？神様、 すごく会いたかったんだから！お願い、お願いだから許して！";
			link.l1 = "いいや、許してくれ、全然予想できなかったんだ……無事でいてくれて本当に良かった、Mary！本当に嬉しいよ！";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "許しと言えば……正直に言うと、あんたを撃つか抱きしめるか迷ってるんだよ。何が起きてるのか、ちゃんと話してくれ、でしょ？";
			link.l1 = "愛してるよ、Mary。君に伝えたかったのは、それだけだ。";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "まあ、それじゃあ全然説明になってないけど…くそっ、チャールズ。あたしもあなたのこと愛してるよ、でしょ？ああ、やっと、 やっとあなたがあたしのそばにいるんだ！";
			link.l1 = "そして、どうでもいいことを話して残された時間を無駄にしたくないの。\nあたしと一緒に来て、でしょ？今夜は絶対にあなたを置いていかない。たとえこのみじめな町に空が落ちてきても、 でしょ？\nもう二度とあなたを離さない。絶対に、でしょ？";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "もしかして…あんたが何をしたのか、あたしは知らない方がいいのかも、でしょ？また一緒になれた、それだけで十分だよ…";
			link.l1 = "あたし、あなたに隠し事なんてないよ。全部話すね…";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "つまり…そのマルキーズがあなたを助けて私を連れ戻したってこと？それに、 イングランドとフランスの間で戦争を始めかけたって？誤解しないでよ、すごくロマンチックだけど、 これからどうなるの、でしょ？";
			link.l1 = "わからないよ、Mary。俺たちはまた一緒になれた、それだけで十分だ。他のことなんてどうでもいい。\n権力者たちが全部をうやむやにできなかったとしても……まあ、王冠のために俺の義務を果たす覚悟はできてるさ。";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "それで、あんたのマルキーズはどうしたの？彼女も連れて帰ってきたの、でしょ？ ポルトガル人が彼女のことをすごく褒めてたよ。あんたがバスティーユ城みたいに彼女の誘惑に耐えたって、 彼は私に断言してた。信じたいんだけど、でしょ？でも、あんたの口から聞きたいの。";
			link.l1 = "マダム・ボトーと俺の間には何もないよ、メアリー。俺が彼女を助けて、彼女も俺を助けただけ、それだけさ。\nバルトロメオの話だけど、彼はどこにいるんだ？";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "もうとっくにいなくなったよ、でしょ？あたしをここに連れてきた後、すぐに帆を上げて出て行ったの。あたし、あの忌々 しい売春宿には絶対行かないって誓ったから、彼はあたしのために部屋を借りて、二週間分前払いして……それで、ただ去って行ったの。あっ、もう少しで忘れるところだった！あなたへの手紙があるんだよ、でしょ？";
			link.l1 = "手紙？ポルトガル人のバルトロメウから？なんだか嫌な予感がするな……";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "さあ、読んでみて。あたしはみんなの様子を見てくる、でしょ？きっと心配してるだろうし。全員無事だった？ 下で一杯か二杯飲んでも気にしないでね、でしょ？あたしが戻るまでまた面倒ごとに巻き込まれないでよ、でしょ？";
			link.l1 = "わかったよ、でも彼らのことは気をつけてくれ、Mary？今夜は酔っ払いを船まで運ぶより、君と一緒に過ごしたいんだ。ああ、君を取り戻せたなんて、まだ信じられないよ！";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "あたしとあなたと浜辺と美味しいワイン――チャールズ、これってすごくロマンチックじゃない、でしょ？もっとこういうこと、しょっちゅうやろうよ、でしょ。";
			link.l1 = "気に入ってくれて嬉しいよ。これからは、こんなふうに二人の時間をもっと作ろうと思うんだ。";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "どういう意味？船に何かあったの？なんでひざまずいてるの？";
			link.l1 = "だって、あたしは君を愛しているからだよ、Mary。君も知ってる、俺も知ってる、世界中が知ってることだ。だから今ここで、この海と空の下で、Mary Casper、君にお願いする。俺と一緒に、俺たちの仲間と神の前で、与えられた日々を共に歩む名誉をくれないか。俺、Charles de Maure、Chevalier de Monperが君に問う……俺の妻になってくれるか？";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "これ、夢に見てたんだよ、でしょ？でも実際に…あたし…答えは分かってるでしょ、Charles――ああ、くそっ！";
				link.l1 = "ははっ！気にしないで、ただのワインだし、このシャツなんて元々好きじゃなかったんだ、でしょ？";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "チャールズ、もちろんよ！でしょ？はい、はい、千回でも「はい」だよ！！！あなたも…この場所も…これ以上幸せなことなんてないよ！！！ああ神様、笑いすぎて頬が割れちゃいそう、でしょ！？";
				link.l1 = "君は俺を幸せにしてくれる、Mary。俺は君に乾杯するよ、俺の燃えるカリブの太陽！";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "あんたに乾杯よ、私の船長で未来の旦那様、でしょ？あんたは私の人生で一番素敵な出来事なんだから！";
			link.l1 = "でも、これはまだ始まりに過ぎないよ――私たちにとってね！そして、私たちのこれからの未来に乾杯、でしょ？この先、 まだまだたくさんのことが待ってるんだから！";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "あんたに乾杯するよ、あたしの船長で未来の旦那さま、でしょ？あんたはあたしの人生で一番素敵な出来事なんだから！";
			link.l1 = "でも、これはまだ始まりにすぎないよ――あたしたちのために！そして、あたしたちのこれからの未来のために！まだまだこれからが本番でしょ？";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "チャールズ、ベノワ院長と話してきてくれる？そしたら先に進めるでしょ？でも、あたしはドレスなんて着ないよ。 気を悪くしないでね。";
			link.l1 = "Mary、どんな服でも君を愛してるし…まあ、分かるだろ、でしょ？君は好きなものを着ていいんだ。文句がある奴がいたら俺に言え！でも、 招待客と式については君に相談したいんだ。";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "あのね、私たちの幸せを心から喜んでくれる人たちのほとんどは、この正義の島に近づくことさえ許されないんだよ、 でしょ？ましてや教会なんて無理。\nだからさ……ここでお偉方たちに囲まれて、期待通りに結婚式を挙げて、それからイスラ・テソロに航海して、 本当の友達とちゃんとお祝いしようよ！どう思う、でしょ？";
				link.l1 = "素晴らしい考えね！やろう、でしょ？私がブノワ修道院長に話してくるよ。誰が来るか決めて、招待状も送らなきゃ……やることがいっぱい、でしょ？";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "あのね、あたし、仲間の船員以外にはあまり友達がいないんだ。だから、気に入った人がいたら誘ってよ、 そしたらあたし嬉しいから、でしょ？";
				link.l1 = "お前の言う通りだよ、可愛い人。ベノワ院長と話して、全部手配するよ。お前には盛大な式がふさわしいからな。";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "お客さんのことは心配しないで、あたしがちゃんとやるから、でしょ？友だちに手紙を書いて、全部手配するよ。\nでもまず教えて、でしょ？結婚式には誰を呼びたいの？";
			link.l1 = "私の理想は、あたしとあなたと、そして一番親しい仲間たちだけ、でしょ？\nここマルティニークの堅苦しい連中の後には、本当の誠実さが欲しくなるよ、でしょ？";
			link.l1.go = "LongHappy_10";
			link.l2 = "今日は忘れられない日にしよう、でしょ？\nみんなを呼んで！誰一人として置いていかないよ！";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "あのね、夕暮れの海で四分甲板にチャプレンを呼んで船上で式を挙げるだけで、あたしは十分なんだよ、でしょ？\nでも、これがあなたの望みなら、お祝いしよう！チャールズ……泣いちゃいそう。抱きしめて、でしょ……";
			link.l1 = "メアリー……";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "わかった、落ち着いたよ。ごめん、全部初めてでさ。でもチャールズ、あたしも組織作りに参加したいんだ、でしょ？ それに、みんなのために宴会も開かないとね、でしょ？でも、教会には全員入りきらないと思うんだ。 酒場と交渉してくるけど、お酒とお金が必要だよ――水夫たちがどれだけ宴会好きか、知ってるでしょ？";
			link.l1 = "よし、それで決まりだね、でしょ？私は何を準備すればいいの？";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "あたしは思うんだけど、 "+sti(pchar.questTemp.LongHappy.MarryMoney)+" ペソで十分、でしょ。 "+sti(pchar.questTemp.LongHappy.MarryRum)+" ラム酒の樽――酒が切れるほど最悪なことはないよ！全部集めたら、すぐ酒場に来て、でしょ？あとはあたしが何とかするから。";
			link.l1 = "いいわよ、ダーリン、そこで会おうね。";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "了解だよ。でもシャープタウンにも行って、そっちの準備もしなきゃね、でしょ？ラム酒は五十樽、 ワインは二十数樽で十分だと思う、でしょ？でも念のために、三十万ペソ必要になるよ、でしょ？";
			link.l1 = "それは大金だけど、この機会にはふさわしいよ。なんとかかき集めてみせるから、心配しないで。\nさて、これから修道院長に会いに行って、それからシャープタウンへ向かうつもりだ。";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "よし、みんな集めるよ、でしょ！？でもシャープタウンに行って全部準備しなきゃね――ガレオン一隻分のお酒が必要だよ！ラム酒百樽とワイン五十樽で十分だと思うけど、 念のために五十万ペソも追加しておくね。飲み物が足りなくて宴が終わるなんて、絶対ダメでしょ？";
			link.l1 = "そうだね、仲間たちを渇きで死なせるわけにはいかないでしょ？全部あたしが用意するから、心配しないで！さて、 これから修道院長に会いに行って、それからシャープタウンに向かうよ。";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "全て準備できたよ、Charles。酒を降ろす手配をしてから、地元の酒場に行って男爵に会って招待状を渡してくる。ここで待ってて、でしょ？";
			link.l1 = "舵はあなたに任せるわ、ね！あたしはどこかでちょっと遊んでくるから。\nスペイン領本土のジャングルへの遠征のほうが、結婚式の準備より楽だなんて、思いもしなかったでしょ？";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "ここはもう終わりだよ、チャールズ、でしょ！全部手配しておいたから。信じて――きっと素晴らしいことになるよ！ただ、一つだけ……地元の酒場が一週間前のお祭りで焼けちゃったの。でも、もうほとんど再建されてて、前より大きくて立派なんだよ！ みんなで入れるはず、でしょ？";
			link.l1 = "また燃やしちゃわないといいけどね。あたし、オールド・ウッドペッカーが本当に好きだったんだ、でしょ？\nまあ、とにかく、まだやることがたくさんあるよ。出航の時間だよ。\nMary……あんたって最高だよ、自分でわかってるでしょ？";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "じゃあ……いよいよだね、でしょ？来賓も揃ったし、教会も準備万端。私たち、普通の夫婦よりずっと近い関係だってわかってるし、 これはきれいなホールでの大げさな言葉遊びにすぎないかもしれないけど――でもさ、あの古代インディアンの都市にいたときより緊張してるんだよ、でしょ！？";
			link.l1 = "絶対に普通のことだと思うよ、愛しい人。あたしも緊張してるんだ、でしょ？ブノワ院長が待ってると思うから、 あたしが行って、式がいつ始まるか聞いてくるね。";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "わかった、ちょっと町を歩いてくるよ、頭を冷やさなきゃ、でしょ？チャールズ……もう後戻りできないって、わかってる？";
			link.l1 = "メアリー、愛しい人よ、あの日出会った瞬間から、俺にはもう後戻りなんてできなかったんだ。 ずっとこの日を心から待ち望んでいたよ。心配しないで、すべてうまくいくさ。";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "そう、でしょ？";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "うん、でしょ？";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "そう、でしょ？";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "私、シャルル・アンリ・ド・モール、モンペール騎士は、メアリー・キャスパー、あなたを妻として迎え、 今日よりこの先、良き時も悪しき時も、富める時も貧しき時も、病める時も健やかなる時も、死が二人を分かつまで、 共に歩むことを誓います。\n神の聖なる掟に従い、主の御前で、この誓いを立てます。";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "私、Mary Casperは、あなたCharles de Maureを夫とし、今日よりこの先、良き時も悪しき時も、富める時も貧しき時も、病める時も健やかなる時も、 死が二人を分かつまで、共に歩むことを誓います。\n神の聖なる掟に従い、主の御前で、この誓いを立てます。";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "アーメン。";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "信じられないでしょ！？あたし…あたし泣いてる、ごめんね、Charles、あたし…鼻まで赤くなっちゃった、でしょ？";
			link.l1 = "メアリー・ド・モール、俺の妻よ、今日もいつもと変わらず美しいぜ！";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "ありがとう、Charles、ありがとう……本当に荘厳で素晴らしかったよ！あたしの人生で最高の日だよ、でしょ！！！見て、みんなすごく幸せそうでしょ？でも、 そろそろお客さんたちと親しくして、お祝いの言葉を受け取る時間だよ！終わったら戻ってきて――酒場でみんなの様子を見に行こう、でしょ？";
			else dialog.text = "ありがとう、Charles、ありがとう……本当に厳かで素晴らしかったよ！あたしの人生で最高の日だよ、でしょ！！！見て、みんなこんなに幸せそうでしょ？ でも、そろそろお客さんたちと親しくして、お祝いの言葉を受け取る時間だよ！終わったら戻ってきてね――Sharptownで待たれてるんだから、でしょ？";
			link.l1 = "すぐにやるよ、可愛い子。キスを一つもらったら、すぐ行くからね！";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "チャールズ、私の愛しい人、うちのお客さんたちと話した、でしょ？";
			link.l1 = "まだだよ、可愛い人。すぐ戻るからね。";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "そう、こんなに一度に「おめでとう」って言われたのは初めてだよ。でしょ？しかも、 そのほとんどが本気だったんだから！";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "うんうん！あたしもまったく同じ気持ちだよ！もちろん、あたしの格好にびっくりしてる人もいるでしょ？それに、 あたし舞い上がっちゃってて、みんなが何言ってるか半分くらい聞き流しちゃった。\nチャールズ、酒場の連中があたしたちを待ってるよ――行かなきゃ。きっと船長を祝福できて、みんな喜ぶでしょ？";
				link.l1 = "今すぐ行こう。だけど…今日という日を酒場の部屋よりも、もっとロマンチックな場所で終えたいんだ。妻よ、 今夜は俺たちの船室で一緒に過ごしてもいいかな？しかも、今は船に見張りもいないし…";
			}
			else
			{
				dialog.text = "そうそう！あたしもまったく同じ気持ちだよ、でしょ？もちろん、あたしの格好にびっくりしてる人もいるけど、でしょ？ それに、あたし、浮かれすぎてて、みんなが言ったことの半分くらい聞き流しちゃったよ。\nでも、Charles、あたしたちSharptownで待たれてるんだよ、でしょ？いつ出航するの？";
				link.l1 = "今すぐだ。客人たちに酒を飲み干されるわけにはいかねえからな！\n妻よ、今夜は俺たちの船室で一緒に過ごしてくれるだろうか？";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "たとえ蚊だらけの無人島の小屋で過ごすことになっても、あんたさえいれば構わないよ。";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "あたしも同じ気持ちだよ。行こう、でしょ？みんながラム酒を全部飲み干して酒場に火をつける前にね。";
			else link.l1 = "あたしもあなたのことが好きよ。じゃあ……出航しよう、でしょ！？";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "ああ、あなた、あたし本当に幸せだよ！今日はなんて素敵な日なんだろう…";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "チャールズ、あいつの汚ねえ頭をぶっ飛ばせ！";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "あたしは大丈夫、でしょ！ナサニエルはどう？生きてるの？";
			link.l1 = "こんなに血が……ダニー、彼は息してる？息してるのが見える！";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "急いで、ねえ、時間を無駄にしないでよ！";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "勝ったでしょ！遅れてごめんね。上の階でこいつらが十人もいて、手一杯だったんだ、でしょ？";
			link.l1 = "大丈夫、ここは私が片付けたよ。やっとジャックとの物語に決着がついて嬉しい…ついに彼は報いを受けたんだ。";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "じゃあ、シャープタウンに戻ろう、でしょ？ナサニエルの様子を見に行かなきゃ。あの狂人、 私たちのために命を懸けてくれたんだから！";
			link.l1 = "そうだよ、愛しい人。行って、あたしがすぐ後ろにいるから、でしょ？";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "ところでね、あなた、マーカスを見つけたよ！貨物室に縛られて、気を失ってたの、でしょ？";
			link.l1 = "生きてる？";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "血だらけだけど、治るよ。うちのバロンは簡単にはくじけないんだ、でしょ？やっと目を覚ましたばかりなのに、 もうケンカしたくてたまらないんだから！";
			link.l1 = "懐かしのマーカス！さあ、岸へ行こう。";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "ごめんね、Charles、でしょ？あたし…あたし、散歩に出てたの。あなたが戻ってきたのを見たし、みんなが生きてて勝ったって聞いたけど、でもあたし…あたし、どうしちゃったんだろう、でしょ！？";
				link.l1 = "すべてうまくいくよ、愛しい人、すべてうまくいくんだ。あたしも悲しいよ。\nでも、私たちは勝ったし、ジャック・バルバゾンは自分の罪の報いを受けたでしょ？";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "ジーノやチャールズのこと、本当にひどい気持ちだよ、でしょ！？聞いたとき、信じられなかったんだから！";
					link.l1 = "あたしも信じられないよ……こんなふうに今日が終わるなんて、思ってもみなかった、でしょ？";
				}
				else
				{
					dialog.text = "また勝ったね、でしょ？あたしの旦那は沿岸同盟の成り上がり男爵たちにとって嵐そのものだよ！仲間は生きてて、 敵は死んでる――それが本来あるべき姿、でしょ。";
					link.l1 = "やったね、愛しい人。やっとここまで来たよ、でしょ？";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "足元もおぼつかないでしょ？さあ、ダニーが郊外に家を見つけてくれたんだ、今は船に戻りたくないよ。\n座って、亡くなった仲間たちに乾杯しようよ――しらふじゃとてもやってられないでしょ。";
			link.l1 = "うん、Mary、行こう。";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "ジーノのことも、チャールズのことも、本当に辛いよ、でしょ！？聞いたとき、信じられなかったんだから！";
				link.l1 = "あたしも信じられないよ……まさか今日がこんな終わり方になるなんて、思ってもみなかった、でしょ？";
			}
			else
			{
				dialog.text = "遅れてごめんね、あなた。ちょっと散歩してたんだけど、あなたを見かけて、急いで走ってきたの！ ジーノが危険は去ったって言った時、ダニエルが私を止めたの。でも、あなたが無事で本当に嬉しい！";
				link.l1 = "あたしもよ、あなた。でしょ？それに、あたしたちが勝ったの。バルバゾンは死んだし、 男爵たちは残った手下を集めてる。戦いは終わったわ。";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "チャールズ、立っているのもやっとじゃない！それに、誰もティチンギトゥを見つけられないのよ。";
			link.l1 = "ヤンがヒントをくれたんだ……サボ＝マティラ入江まで散歩しよう。何人かが彼がそっちに向かうのを見たってさ。";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "ほら、うちの無口なインディアンがいるでしょ？\nさあ、ダニーがこのはずれに家を見つけてくれたんだよ――チャールズ、あんた本当にくたくただね、でしょ？";
			link.l1 = "そこにあるよ……あたしをさらって、あなたの美しさで。でしょ？そして朝になったら、全部悪い夢だったみたいに思わせてよ。";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "誤解しないでね、旦那。教会は豪華だったけど、ここは雰囲気がずっと心に響くの、でしょ？\nまあ……それだけよ、チャールズ。私たちの苦労は全部終わったの。これからはゆっくりできるわ。";
			link.l1 = "まあ、「全部」ってわけじゃないよ、俺の妻よ――これからも一緒に生きていくんだ！未来がどうなるかなんて分からないさ。だから、行こうぜ、仲間たちと一杯やって、 それから――覚えてるだろ？船室で、ワインと、俺たちだけで…";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "私の旦那…その言葉、すごく甘く響くよ、でしょ？これでもう、あなたは永遠にあたしのものだよ。";
			link.l1 = "あたしはもうずっと前からあなたのものだったよ、でしょ？そして今からは永遠に、あたしの愛しい人…";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "あたし、本当に幸せだよ、チャールズ！そしてこれからは、何をするにも一緒だよね、でしょ？";
			link.l1 = "もちろんよ、ダーリン！肩を並べて、ずっと一緒にいるんだから、でしょ？";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "この病気はお前の女たちにかなり影響を与えてるみたいだな、ロドリゴ。編み物でもさせて、暇を持て余させるなよ！";
			link.l1 = "この話は堂々巡りだね。明日教会に行くって約束したでしょ？もちろん、お祈りのために、でしょ？";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "あたし、あなたのこと誇りに思うよ、愛しい人！";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "「チャールズ…」";
			link.l1 = "メアリー、何を考えているんだい？";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "（笑）あたしとアランも、ここであなたがやったことを正義の島でやりたかったんだよ、でしょ？";
			link.l1 = "「あなたの…アラン？」";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "とんでもない夢追い人だったよ、彼は——もし生きてたら、あんたと最高の友達になれたはずだ。";
			link.l1 = "私たちの好みは、少なくとも一つの点では確かに同じだね……";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "何だって？ははは！もう、黙ってよ、チャールズ！\nどっちにしても、すごいことだよね…あたしたち、この人たちにこんなに喜びを与えたんだ、でしょ？";
			link.l1 = "俺たちは奴らにチャンスを与えた。あとは自分たちでやったんだ。\nそれで……どう思ってるんだ？";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "後で会いに来てくれたら、わかるよ……";
			link.l1 = "あたし、やるよ、でしょ！";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "暗くて狭い場所が好きなんだ。落ち着く気がするの。やっと自分の考えをまとめられる、でしょ？\nまるで悩みなんて全部…消えちゃったみたい！この感覚、ずっと恋しかったんだ…";
			link.l1 = "医者に診てもらう必要があるよ。";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "まるでセレス号に戻ったみたいでしょ？";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "…残念ながら、私は一人じゃないんだ。\n静寂の中で、闇の中で、孤独の中で――ああ、それなら完璧だったのにな。";
			link.l1 = "夢を見続けろよ、Mary Casper。";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "一度、カニが私のベッドに入り込んできたのよ――あたし、それを切り刻んで食べちゃった、でしょ？";
			link.l1 = "夢を見続けてろよ、Mary Casper。";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "仮面のクソ野郎！痛っ！助けて、ねえ、お願い――この鉄格子を壊さなきゃ！";
			link.l1 = "静かにして！どうすればいいか考えてるんだから！";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "ねえ、あんた、あの仮面のクソ野郎どもがどこにでもいるのよ！船体に穴を開けて、カニみたいに這い回ってるんだから！ 全部ぶった斬らなきゃ、でしょ！？";
			link.l1 = "メアリー、ここにいて、指揮を執ってくれ！\n船を戦場から離して！もう一度乗り込まれたら生き残れないぞ！";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "どこへ行くつもりなの？あたし、あんたを行かせる気なんてないよ、でしょ！？";
			link.l1 = "エルキュールと俺たちの仲間を助けなきゃいけないんだ！信じてくれ、メアリー！";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "了解だよ、ダーリン！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "勝利だよ！こっちにおいで、ねえ！一時間か二時間、あんたが欲しいの、でしょ？";
			link.l1 = "「あっ…」";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "行こう！";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "やあ、Hercule！会えて本当に嬉しいよ、白髭さん！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "メアリー！メアリー、待ってくれ！君の報告が必要なんだ！";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "え？まあ、勝ったよ、でしょ？あのクソ船は逃げていったし、あたしは野郎の頭を真っ二つに割ってやったんだよ、 でしょ？\nふう、くそっ、ボタンめ！";
			link.l1 = "ああ、Mary…";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "ああ神様、見ないで、あなた！あたし、もう……ふう！";
			link.l1 = "頑張れ、あんた。あたしが来たよ！";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"！ちょっと話があるの、でしょ？本気なんだから！";
				Link.l1 = "どうしたんだ、Mary？何か問題でもあるのか？";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("聞いてるよ、親愛なる船長！","「うん、でしょ？」 "+pchar.name+"「聞いてるよ、でしょ！」","俺に仕事があるのか、 "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "メアリー、これから古代インディアンの都市テヤサルに行くつもりだよ。嘘はつかない、この旅は本当に危険だし、 しかも前に話したあの偶像を使うことにもなるんだ。君は……ついてきてくれるかい？";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary、詳しい報告をしてくれ。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "私たちが港に寄港するたびに、特定の商品を毎回購入してほしいんだ。";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "メアリー、君の助言が必要なんだ。";
				Link.l3.go = "fugas";
			}
			Link.l1 = "メアリー、君に命令があるんだ……";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("ねえ、今すぐあなたが欲しいの。いいでしょ？","メアリー、しばらく…一緒に過ごさないか？二人きりで、でしょ？");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("メアリー、一緒に部屋を借りて泊まらないか？","愛しい人、二人きりで過ごしたいの…でしょ？\n部屋を借りて、数時間だけ全部忘れちゃわない？");
				Link.l2.go = "room_sex";
			}
			link.l9 = "何でもないよ、Mary。";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "チャールズ、あの子は本当に美人でしょ？\n喫水線の下の穴も直したし、帆も乾かしたよ。\nな、何を期待してたの？そんな目で見ないでよ、でしょ？あたし、会計士なんて勉強したことないんだから。";
			Link.l1 = "ごめん、Mary、本当にちゃんと考えてなかったんだ。";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "チャールズ、あたしは大丈夫だよ！もうコートも剣も持ってるし。でも気にかけてくれてありがとう、優しいね、でしょ？ ";
			link.l1 = "でもあたし、全然……まあ、いいや、忘れて、でしょ？大丈夫だよ、あたしたち。";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "命令でしょ？";
            Link.l1 = "ここに立って！";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "あたしについてきて、遅れないでね、でしょ！？";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "メアリー、火器の弾薬を交換してくれ。";
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
            dialog.Text = "すぐに、愛しい人よ！";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "すぐにだよ、愛しい人！";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
