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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "バグだ。開発者に伝えてくれ。";
		link.l1 = "ああ、いいぜ。";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "おう、また勇敢な水夫か！お前みたいな奴はよく知ってるぜ、俺のくたばった片目はちゃんと見抜いてるんだ、ははっ！ なぜかって？";
			link.l1 = "別の件について聞くが、地元の……ええと、あの店の女主人に対する借金のことだ。彼女からお前に借金を思い出させてくれと頼まれたんだ。 何とかしたほうがいいぜ、さもないと明日には衛兵に頼むことになるぞ。";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "地元のやつは……くそっ！ヨハンナ、あの女が俺にこんな仕打ちをするなんて！本当か？ 本当に俺をたった数枚のクソみたいなコインのために牢屋送りにすると言ったのか？";
			link.l1 = "まったくその通りだ。彼女がそう言ったんだ。俺の任務はこれで終わりだろう、さらばだ、アヴェンデル旦那。";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "待ってくれ！頼む、待ってくれ！あんた、経験豊富な船長に見えるぜ。きっと小銭くらい持ってるだろう？ 俺はすっからかんでな、古い友人ってことで酒場の親父がツケで酒を注いでくれるだけさ。俺の…提案を聞いてくれ！あんたが俺の借金を肩代わりしてくれたら、俺もあんたに分け前をやる\n商売があるんだ…とんでもなく儲かる商売だ、くそっ、俺の尻が呪われてもいい！血塗られた錨に誓う、信じてくれよ船長――名前は知らねえが！\nたった一つ、小さな借金、たった一万ペソを肩代わりしてくれりゃ、 あんたは新世界中の売春宿を全部買えるくらいの金を稼ぐチャンスを手にできるんだぜ！どうだ？あんたがくれりゃ、 俺もやる、正直者の取引ってやつさ…";
			link.l1 = "宝を約束するみすぼらしい奴め。そんな戯言はごめんだ、俺はお前みたいな奴に慈善なんてしねえ。金を用意しろ、 さもなきゃすぐに砦の地下牢で暮らすことになるぞ。じゃあな！";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "分け前だと？酔っ払いの馬鹿の言葉なんぞ、なぜ信じなきゃならねえんだ？空っぽの約束のせいか？";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "聞いてくれよ、船長！ひっく、もし俺が嘘ついてたら撃ち殺してくれて構わねえ！でも本当のことを言ってるんだ！ 考えてみろよ、もし俺の嘘がバレたら、その腰に下げてる美しいヤツで俺の腹をかっさばいてもいいぜ！くそっ、 その柄だけで俺のしけた借金の五倍はするだろうよ！どうだ？あんたに損はねえだろう！？";
			link.l1 = "お前の説教はもううんざりだ。じゃあな。";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "わかった、ユーゴ……お前の言うその馬鹿げた話を信じてみるとしよう。ただし、覚えておけよ。俺が戻った時に、 俺の金が無駄じゃなかったと納得させてもらうぞ。そうでなきゃ、お前の首が危ないからな。";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "脅す必要はねえ、わかったよ。約束するぜ、船長！俺たちは金持ちになるんだ！この忌々 しい借金を返したら戻ってきてくれ、そしたら…話そう！ああ、必ずだ！お前を仲間外れにはしねえからな！";
			link.l1 = "よかろう、お前の借金は帳消しにしてやる。だがな、ヒューゴ・アヴェンデル、お前の「提案」 が俺を満足させるよう祈っておけよ。";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "船長、できるだけ早く戻ってくれ――この仕事、逃げちまうかもしれねえぞ。";
			link.l1 = "ああ、ああ、すぐに借金を返すよ。";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "戻ったな、船長！嵐とくそったれな雷にかけて、あんたに会えて本当に嬉しいぜ！俺の借金はどうなったんだ？";
			link.l1 = "片付けたぜ、次はお前の番だ、ヒューゴ。自分の話をしてみろよ、少しは信じられるようにな！";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "心配するな、船長！俺が賞金稼ぎだったって知ってたか？いや…昔の話だ。運がなかったんだろうな。もしかしたら、あの悪魔ですら、俺ほど負け犬じゃなかったかもしれねえ。 最後の仕事で全部失っちまった…仲間は俺を見捨て、借金のせいで船まで売る羽目になったんだ…";
			link.l1 = "お前の英雄的な過去についてはすでに聞いている。用件に入ろう、ユーゴ、俺の忍耐を試すな。";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "「ああ、ああ、船長…」"+GetFullName(pchar)+"…そうだろ？俺もお前のことをちょっとは知ってるぜ。だが、くそ、重要なことじゃねえ。 バルトロメウ・ザ・ポルトガルって名前、聞いたことあるか？";
			link.l1 = "バート・ザ・ポルトガル人か？もちろん知ってるさ。誰だって知ってるだろう。奴は海賊で、殺し屋で、 俺の知る限りクズ野郎だ。で、お前の話に奴はどう関わってるんだ？";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "あいつはこの件でとんでもなく重要な役割を果たしてやがるんだ！俺はこの一年半、ずっとあいつを追い続けてきた。 オランダ東インド会社はあいつの首に高額な賞金をかけてる。だが、俺は失敗し、すべてを失った。そして最近、 会社はあいつの生け捕り報酬を三倍にしたんだ――生きたまま、だ。くそっ！";
			link.l1 = "当然だが、生け捕りにするのは簡単な仕事じゃねえ。まあ、そんなこと俺には関係ねえだろ、ユーゴ？どうやらお前、 俺を騙そうとしてるんじゃねえか！";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "俺はやるつもりなんてなかったぜ、船長！なあ、地元の医者のピーター・ヴァン・スタルっていう、とても親切な男が、 頭痛を治す薬をくれたんだ！それでな、その医者が自分の家に三日近くもいなかったんだよ、そして…\n";
			link.l1 = "ユーゴ、俺の我慢ももう限界だ！あのご婦人に刃物では刺さないと約束したが、拳なら問題ねえだろう！明日、 お前の頭はどんな薬でも治らねえって誓うぜ！";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "待ってくれ、船長！お願いだ！聞いてくれ、俺は医者の家の近くで何人かの男を見かけて、そいつらを見覚えがあるんだ。 奴らは「アルバトロス」――あの忌々しいポルトガルのフリゲートの連中だ！しかも、そのうちの一人が自分たちの船長の健康について話してたんだ！ ほら、今見てくれ、 "+pchar.name+"バルトロメオがここ、この街にいるんだ！俺たちの鼻先で、やつは怪我してるか病気なんだろう、 だから医者が必要なんだよ、くそったれめ！\nポルトガル野郎が全員の手下をここに連れてきたとは思えねえが、俺一人じゃこの騒ぎは始められねえ！ お前なら呪われた剣の扱いもお手のもんだろう？屈強な奴らを何人か連れてきてくれ、 そしたらあのネズミ野郎を見つけ出す！捕まえて役人に突き出すんだ！\nそうすりゃ二千枚の金貨が俺たちの懐に入るぜ！";
			link.l1 = "いやだ、ユーゴ。お前の話はもううんざりだ。たとえお前が正しくても、こんな面倒には関わらねえ。じゃあな。";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "ふむ、面白いな。奴がどこに隠れているか知ってるのか？うまくいけば分け前の話もできるが、 もしお前の言うことが本当なら、今すぐ急がなきゃならねえぞ！";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "いいえ、どこにいるかは知りませんよ、船長。あいつらを追いかけるのは怖すぎました。もし片目の奴に見つかったら……ふっ！でも、あんたの連中と一緒なら、この町中をくまなく探せるはずだ。仲間を呼んでくれ、さあ始めようぜ！くそっ、 オランダのドゥブロン金貨が俺たちを待ってるんだ！こんなチャンス、一生に一度しかねえ、ニシンでもかじってやるよ！ ";
			link.l1 = "感心するほどのやる気だな……「偉大な」賞金稼ぎさんよ、ちゃんと席を立てるといいがな。俺はすぐに捜索を始めるぜ、ついてきたけりゃ勝手にしろ――ただし、あんまり邪魔すんじゃねえぞ。";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "ああ、ああ、船長、ちょっと酒を飲み終わらせてくれよ、そしたらすぐに行くぜ……どこから始めるんだ？";
			link.l1 = "どこだ！？…俺は行くぜ、お前がいようがいまいがな。";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "家を間違えてるぜ、野郎。さっさと失せな！";
			link.l1 = "ふむ。ここが正しい家だと思うんだが……";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "まあ、警告はしたぜ……";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "いっぱいに帆を張れ、高く掲げろ、息子たちよ…砲門の用意だ！…アッハッハ…おお、俺の美しい船よ…";
			link.l1 = "ふむ、あいつは生きてるだけでも運がいいな……";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "おお神よ、あなたは誰だ！？武器を下ろしてくれ！ここには病人がいるんだ！";
			link.l1 = "お前のその「病人」ってやつは、あんたが今まで見てきた人間よりも多くの人を殺してきたんだぞ、先生。離れろ！";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "あいつは俺の患者で、立つのもやっとなんだ！わからねえのか？頼む、刃を下ろしてくれ！お願いだ！";
			link.l1 = "「そいつの何がいけねえんだ、くそっ！？」";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "きっとあいつの傷のせいだろう、毒が塗られたカリブの武器でやられたんだ……それに、あいつをここに運んできた連中が言うには、もしあいつが死んだら、俺も殺されるってよ！ だが俺はできる限りのことをしてるんだ、それをあいつらに伝えてくれ！";
			link.l1 = "あの連中のことは心配するな、先生。俺の連中があんたの家を見張ってるし、俺は総督に会いに行かなきゃならねえ。 あいつは喜びすぎて小便ちびるかもな。俺が戻るまでここを離れるんじゃねえぞ、先生。";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "俺はここを離れねえ、心配すんな。さっさとあいつを役人に引き渡して、この悪夢を終わらせようぜ。";
			link.l1 = "もちろん、今向かっているところだ。";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "やったぜ、船長！見つけたぞ、もうすぐ俺たちは金持ちだ、言った通りだろう！これからどうする？";
			link.l1 = "そうだといいな、ユーゴ。まあ、とにかく、まだ終わっちゃいないぜ。俺が総督のところへ行って、 報酬について話し合わなきゃならねえんだろう？";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "いやいや、船長！あの忌々しいトマスのところへ行っちゃいけねえ！信じてくれ、この悪党は俺たちの捕虜を奪うし、 運が良くてもコーヒー一杯ご馳走して終いだぜ！閣下はずる賢い奴だから、 報酬を全部もらいたいならキュラソーまで航海しなきゃならねえ！さもないと、ポルトガル人は砦に連れて行かれ、 俺たちは物乞いみてえに追い払われちまうぞ！\n";
			link.l1 = "「まあ、本当にそう思ってるんなら……」";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "俺はそうだ、船長、くそったれ間違いねえ！だがな、バルトロメオの手下どもが町のどこかにいるはずだし、 守備隊の目も引きたくねえ、これも確かだぜ！どうやってポルトガル人をあんたの船まで連れて行くか、 しかも目立たずにやる方法を決めねえとな。";
			link.l1 = "……仕方ねえ……ウィレムスタッドまであいつのフリゲートと戦いたくねえんだ。何かいい策はあるか？";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "ああ、あるぜ。まずはあいつにもっと高貴な服を用意しねえとな、 それから酔っ払った士官として裏口から引きずり込むんだ！誰もあいつがくそったれな海賊だなんて疑いやしねえ、 俺を信じろ！";
			link.l1 = "うーん、これでいいのか自信はねえが、他にいい策もねえしな。乗客のために上等な布を手に入れてくるぜ。 お前はここでバートと医者を見張っててくれ。";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "心配するな、船長。ポルトガル野郎は俺の信頼できる見張りの下にいるぜ、へへ……";
			link.l1 = "私はそう信じたいのだが……";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "兵士たちが見えないな。 "+GetAddress_Form(NPChar)+"。奴らはどこだ？状況を伝えればすぐにあいつを逮捕すると言ったじゃねえか。それなのに、 なぜ兵士たちがここにいないんだ？";
			link.l1 = "兵士は来ないぞ、ヴァン・スタール旦那。俺が自分でやるつもりだし、 あんたの患者をできるだけ早くキュラソーへ連れて行かねえといけねえんだ。";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "船長、聞いてくれ、俺にはあいつの傷をどうすることもできねえ、せいぜい熱を少し下げるくらいだ。 ほとんど意識がなくてうわごとばかり言ってるし、何もしなくても死ぬのは間違いねえ、 海の揺れで数日中には命を落とすだろう。役立つ薬をいくつか渡しておく……";
			link.l1 = "いや、先生、あんたも一緒に来てもらうぜ。まず、俺は医術なんて全然ダメだし、それに、 ここに残ってポルトガル野郎どもに船長がどこ行ったか説明したいとは思わねえだろ？\n";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "…そうだな、君の言う通りかもしれん。しかし、この海賊は実にしぶといぞ。 インディアンの武器で軽傷を負った者たちを何人も見てきたが、みんな三日と経たずに死んだ。だが、奴の『仲間』 によれば、もう一週間もこの状態らしい！それでも、俺は奴が外洋の船上では長くはもたんと思う。三日だ、 それ以上は無理だ！\nそれが我々に残された時間だ。";
			link.l1 = "鳥でさえ三日でキュラソーには辿り着けねえよ。\nだが、俺にできることが分かった気がする！アンティグアのセント・ジョンズに住んでる……知り合いがいるんだ。致命傷でも治せる腕を持ってる奴さ。今、俺たちを助けられるのはそいつだけだ。\n目標は単純――ポルトガル人が死ぬ前にそこへ辿り着くことだ。\nさあ、医者、荷物をまとめろ。すぐに出航するぞ。お前の患者は次に移される！";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "残念だな、船長。俺たちは負けちまったし、あの忌々しい金も見られねえ。さらばだ。";
			link.l1 = "さらばだ、Hugo。";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "ドク、患者を上陸の準備させろ。\nロングボートは用意できてる。急げよ！";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "「今向かっている」 "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "この家は血まみれの薬の臭いが充満してやがる！ここでポルトガル人が死んでたら本当に驚きだぜ； この臭いを吸うだけでどんな病気も治っちまいそうだ！\nそれに、この悪臭のおかげであいつの船員どもに簡単に見つかっちまうぞ！";
			link.l1 = "ユーゴ、冗談はやめてくれ。家の見張りに何人か通りに残してあるが、 客人のためにもう一人見張りがいても無駄じゃないだろう。あいつから目を離すな、ついでに悪態もやめるようにしろ。 さもないとジーノが自慢の薬を飲ませるぞ、あいつならきっと治してくれるさ。";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "心配しないでください、船長！俺が金はしっかり見張っておくぜ、あいつが元気でも絶対に逃がさねえ！ それとお願いです、もう薬の調合は勘弁してください！";
			link.l1 = "ほら、やればできるじゃねえか。油断するなよ、俺は行かなきゃならねえ。";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "もう出発かい、船長？いいぞ！ちょうどいい時間だ！さっき通りで怪しげな……いや、怪しい連中を何人か見かけたぜ。ポルトガル人には見えねえが、何かを探してる様子だった。気をつけねえとな、 船長！";
			link.l1 = "わかった、警告ありがとう、Hugo。船へ行こう。";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "船長、この会合をずいぶん長く待っていたんだぜ！それで、そっちの連れは誰だ？ ポルトガル人のバルトロメウ本人じゃねえか、ははっ、豪胆なピエールの言ってた通りだ――間違いなくあいつだ！下がってろ、船長、こいつは俺たちが連れて行く。誰も傷つかずに済ませてやるからな。\n";
			link.l1 = "悪いが、旦那、一体てめえは何者だ？邪魔するな、さもねえとお前ら全員、明日を迎えられねえぞ！";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "おいおい、なんて怖そうな野郎だ、みんな見てみろよ！ハハハ！いいか、坊主、 レオ・コードとその金の間に立つんじゃねえ！俺たちは半年近くもポルトガル野郎を追いかけてきたんだ、 やっと捕まえたってわけさ。だからそのつまようじみてえな剣を下ろして、とっとと消えな！まだ息してるうちにな。 俺たちはそこまで欲張りじゃねえ、死体でも十分だぜ、ハハハ！";
			link.l1 = "もう十分だ。踊ろうぜ、旦那たち！";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "ここは何かおかしいと思ってたんだ！よくやったな、船長！だが、もう行く時だぜ。あの忌々 しいレオ・コードの野郎はこの辺りに手下も多いし、立派な船も持ってやがる！この島から早く逃げねえと！";
				link.l1 = "いい指摘だな、ユーゴ。それに、お前が隠れていた穴に弾が一発も撃ち込まれなかったのは本当に嬉しいぜ。";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "残念だな、船長。俺たちは負けちまったし、あの忌々しい金貨も手に入らねえ。さらばだ。";
				link.l1 = "さらばだ、ヒューゴ。";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "お、俺は後方を守ってたんだ、船長！あんたは俺がいなくても十分やれてたけど、 もし誰かが通りの反対側から襲ってきたらどうする？船まで走る時間なんてなかったぜ。";
			link.l1 = "もしかして、それでお前の仕事がうまくいかなかったんじゃねえか？まあいい、もう話は終わりだ、船に行くぞ！ 時間がねえ！";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "船長、ポルトガル人が本当に具合悪そうだ、止まらなきゃいけねえ！";
			link.l1 = "だからこそここに来たのだ、van Stal旦那、我々の旅ももうすぐ終わる。酒場で部屋を借りて、囚人はそこで数日過ごすことになる。";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "旦那船長、ポルトガル人のことは俺が面倒を見るぜ、あいつには完全な休養が必要だ。";
			link.l1 = "わかったよ、先生、大丈夫だ。くそっ、いつまでこの海賊の面倒を見なきゃならねえんだ？ こんなのあいつのためにならねえ、必要なことじゃねえ！まるで子守りとして雇われたみたいだし……ああ、すまねえ、先生、ちょっと限界でさ……また後で会おう。";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "旦那、あんたが船長か "+GetFullName(pchar)+"、今日ちょうど我々の港に船が到着した方ですか？";
			link.l1 = "おっしゃる通りです、どうお手伝いしましょうか？";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "我が植民地の総督、ジャック・ディル・デュ・パルケ閣下がお待ちです。急ぎの用件ですよ！";
			link.l1 = "わかりました、旦那、今日は閣下を訪ねます。";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "マルティニークに到着しましたぜ、船長！俺たちの金ももうすぐ手に入りますぜ…";
			link.l1 = "ポルトガル人がウィレムスタッドに着くまで生き延びればの話だ。ヒューゴ、俺は船に行かねえといけないから、 医者とその患者の見張りはお前に任せるぜ。";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "船に行くのか？なぜだ？俺を手伝うためにお前の部下を何人か貸してくれるのか？ お前がいない間に何かあったらどうするんだ？";
			link.l1 = "申し訳ありませんが、無理です。ここであなたを脅かすものは何もないと思います。守備隊は警戒態勢にあり、 普段よりも兵士が街に多くいますから、何かあれば彼らを呼んでください。島の近くで大型船が目撃されましたが、 どうやら海賊船のようです。そして総督閣下からは、私の船で巡回して島を強化するよう命じられています。";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "船か？海賊船か？アルバトロスかもしれねえ！あるいは、俺たちの古い友人レオ・コードの仲間かもな！";
			link.l1 = "あるいは、ただの普通の海賊船かもしれねえ。だがな、ユーゴ、この船が俺たちの首を狙って来たんなら、 地元の巡回隊と一緒に、総督の金のために立ち向かった方がいい。旅の残りをずっと背後を気にしながら過ごすより、 よっぽどマシだ。もしこの警報が間違いだったとしても、何日か酒場で尻を温めずに済むだけの話さ。";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "考えてみてくれ、船長。ダム……いや、あのポルトガル人を無防備のままにしておくのは賢明か？ あいつのフリゲート艦がうろついているかもしれねえんだぜ。総督の報酬を受け取ることで、 俺たちの取り分を危険にさらしてるんだ！";
			link.l1 = "もういい、ユーゴ・アヴェンデル！ここでは俺が船長だ、最終決定は俺が下す！だから俺の命令に従え。\n酒場へ行って、医者とポルトガル野郎から目を離すな。俺が戻るまでだ。";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "やっと戻ったな、船長！残念だが悪い知らせがある――ポルトガル野郎はいなくなっちまったし、医者もいねえんだ！";
			link.l1 = "「どうしてだ！？それでお前はその時何をしてやがったんだ、この間抜け野郎！？」";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "あれは間違いなく『アルバトロス』号だったに賭けてもいいぜ。ポルトガル野郎どもが酒場に入っていくのを見たんだ、 俺は……俺は逃げちまった。すまねえが、片目の犬に会うなんて、いくら金を積まれても無理だぜ！";
			link.l1 = "ちくしょう！せめて酒場で何があったか教えてくれよ？";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "何も見ていないって言っただろう。フランツ・ガルケとその手下たちを見た瞬間、すぐに台所を駆け抜けたんだ…あまりにも危なかった！昨日の夕方の出来事で、どうやって知らせればいいのかわからなかったんだ…";
			link.l1 = "ああ、確かにお前は勇敢で機転の利く男だな……よし、もう一度だけチャンスをやろう。俺たちで奴らを見つけるぞ。この悪党は長いこと俺が取っておいたし、 今では俺の持ち物みたいなもんだ。まだ奴らを捕まえる時間はある、まずは酒場から始めよう。お前の逃げ足よりも、 何か見たやつがいるかもしれねえ。行け、準備しろ！";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "聞いたか、船長、あいつは片目の犬のことを話してたぜ、俺が最近話したやつだ。 それから舌足らずのカスティーリャ人はエルナンド・バスケス、あの血塗れのドン――ベラクルスの殺し屋だ、俺は奴を見てねえ！";
			link.l1 = "落ち着け、ユーゴ。バルトロメオはまだ島にいるはずだ。体調は少し良くなっているかもしれねえが、 まだ本調子じゃねえ。どこにいるかも心当たりがあるんだ！必ず奴らを捕まえるぜ、報酬を逃す気はねえ。 臆病者じゃねえなら、俺について来い――まだ終わっちゃいねえぞ。";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "質問が多すぎるぜ、船長……待てよ、お前、フィリップスバーグのあのずる賢い野郎じゃねえか？ずっと俺たちから逃げ回ってたくせに、ほら見ろ――とうとうここで会ったな……";
			link.l1 = "ざまあみろ、このクズ野郎！";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "…てめえ、このクソカニ野郎、全部吐かせてやるからな、信じろよ、このクソネズミめ！それから、 お前はトップセイルじゃなくてヤードアームに吊るされるんだぜ…で、てめえは一体誰だ？くそっ、あの猿どもはまったく信用できねえ！ 結局いつも全部自分でやらなきゃならねえんだよな…\n";
			link.l1 = "「邪魔してるかい、旦那方？」";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "いいタイミングだな……今日まで俺を生かしてくれたこと、感謝すべきかもな？";
			link.l1 = "おっしゃる通りです。私の名は "+GetFullName(pchar)+" そしてお前、ポルトガル野郎、まだ俺の囚人だぜ。だから質問なんかするな、行くぞ。";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "待ってくれ、船長……町にはバスケスの手下が大勢いるんだ、このままじゃ通してくれねえよ。俺にも剣をくれ、 そうすりゃずっと勝ち目が上がるぜ。";
			link.l1 = "仲間とうまくいってねえのか？まあいい、剣が一本増えるのは歓迎だぜ。死体の武器を取って、俺のそばにいろ！";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "俺が武器を渡して、背中を向けた瞬間に斬りかかるなんて考えるんじゃねえぞ！俺のそばにいろ。";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "心配するな、船長。俺はもう二度とバスケスの手には落ちるくらいなら死んだ方がマシだぜ。";
			link.l1 = "まあ、実はまだお前に死んでほしくねえんだ。行くぞ、時間がねえ！";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "残念だが、もしお前を殺したかったら片目の奴に手を貸してやったさ……";
			link.l1 = "だが、お前も俺を助けなかっただろ、だから黙って動け！";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "くそっ！あいつらだ！皆殺しにしろ！";
			link.l1 = "またかよ……さあ来い、この野郎ども！";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "素晴らしい！お前は片目の犬を仕留めたんだな、まさに傑作だぜ！あいつの手下を何人地獄送りにしたんだ？";
				link.l1 = "俺は戦ってたんだ、数なんて数えてねえよ。で、ヒューゴ、お前はどこにいたんだ？";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "残念だな、船長。俺たちは負けちまったし、あの忌々しい金貨も見られねえ。じゃあな。";
				link.l1 = "さらばだ、Hugo。";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "俺は……安全に撤退できるようにしてたんだ……まあ、いわば後方を守ってたってわけさ。";
			link.l1 = "さて、これで終わりだ、ユーゴ・アヴェンデル。お前の臆病ぶりには俺の想像を超えたぜ。 あの戦いがどれだけきつかったかわかってるのか？俺たちはかろうじて生き延びたんだぞ！";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "落ち着いてくれ、船長…。隠れていたのは認めるよ。でも、このチャンスを見つけてきたのは俺だぜ！ ポルトガル人のところへ案内したのも俺だったのを覚えてるだろう？まあ…あんたの正当な怒りを考慮して、報酬の三分の一だけで手を打とうじゃねえか。";
			link.l1 = "そりゃあ見事だな！今さら値切るつもりか？いや、旦那、あんたの役目はもう終わりだぜ！ あんたはサン・ピエールの酒場で金を失ったんだ。そこに置いて逃げたんだから、もうあんたの出番は終わりだよ。\n";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "船長、明らかに大げさだぜ……よし、四分の一で手を打とう……いや、五分の一だ！一割だぞ！";
			link.l1 = "俺の我慢を試すんじゃねえ！消え失せろ！今は特に、時間がねえってのに、腰抜けなんざ俺の仲間にはいらねえんだ！";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+"、ちょっと不公平じゃねえか？";
			link.l1 = "因果応報だ、ユーゴ……お前は自分で選んだんだ、じゃあな。自分で結論を出せ、そしてそんな冒険にはもう首を突っ込むな。 お前には明らかに向いてねえよ。";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "バラストを捨てるのかい、船長？まったくだな、はは……バスケスはまだ自由の身だし、アルバトロス号には大勢の男と大砲がある。 俺の上等なズボンを古いハンカチと賭けてもいいが、エルナンドが俺たちを逃がすはずがねえよ。";
			link.l1 = "さて、どうやら自分たちで挨拶しに行かねえとな。行け、ポルトガルの旦那、口は慎んでおけよ。 できるだけ早く錨を上げるぞ。";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "何をぐずぐずしてやがるんだ、くそっ！？";
			link.l1 = "エルナンド・バスケスはどこだ？話せば命は助けてやる。";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "てめえのくだらねえ質問なんざ、地獄へ持っていきやがれ！";
			link.l1 = "お先にどうぞ…";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "そしてここに来てくれたな、勇敢な友よ。やっとちゃんと話ができる！おめでとう、船長――片目の犬を仕留めて『アルバトロス』を沈めるなんて、並大抵のことじゃなかったぜ！本当に、 俺の命を救うためにこれほどまでしてくれた……もしかして、礼を言うべきかもしれねえな？";
				link.l1 = "お前が絞首台で踊る時か、ウィレムスタッドで用意された何かにかけられる時には、俺に感謝することになるぜ。";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "そしてここに来てくれたな、勇敢な友よ。ようやくゆっくり話ができる！おめでとう、船長――片目の犬を倒すとは、まさに誉れ高き歌に値する偉業だ！本当に、私の命を救うために多くのことをしてくれた……もしかしたら、感謝すべきかもしれんな？";
				link.l1 = "ウィレムスタッドでお前のために用意された絞首台か何かの上で踊ることになった時、俺に感謝することになるぜ。";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "信じられない！この二週間、君は俺の命を救い続けてくれたし、自分の家に連れてきてくれて、戦いでも守ってくれた……それなのに、今度は俺を死地に送り出すつもりか？とても信じられねえ……実は、今じゃほとんど君のことを友達だと思ってるんだぜ、はは。";
			link.l1 = "名誉に訴える海賊だと？ポルトガル野郎、冗談じゃねえか？俺がお前を生かしておいたのはただ一つの理由だ――殺人者であり悪党であるお前を法の裁きにかけるためだけだぜ！";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "俺の友達…皮肉に聞こえるな。だが、それでもお前の言う通りだ。俺がそんなことをするのはおかしいだろう、ポルトガル人…。";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "「ああ、もう十分だ、船長。どうせ俺を生きて帰らせたご褒美に会社が約束した金が目当てだったんだろう？ 自分以上に正直者ぶるなよ、旦那、それはお前には似合わねえぜ。」";
			link.l1 = "自分を裁けるのは俺だけだ。だから、この話はここで終わりにしよう。\nウィレムスタッドへ出航する時間だ。";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "最近でもまだ人々の中に少しは誠実さが残ってるようだな……だが金がいつも邪魔をするんだ、なあ、船長？";
			link.l1 = "絞首台行きの海賊からそんな言葉を聞くとはな、ポルトガル野郎。今回は見逃してやる……理由は聞くな、とにかく最初の港でとっとと消え失せろ。覚えておけ、次に会った時はこんなに甘くはしねえからな。";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "本当？それは嬉しいよ、船長！ラム酒をここに持ってこさせてくれないか？ほら、お前さんの騎士道精神と俺たちの仲、 それに俺の刑の延期を祝ってさ。";
			link.l1 = "悪ふざけはやめろ、最初の岸に着くまではまだ俺の囚人だぜ。さらばだ。";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "なるほど……つまり絞首台行きってわけか。まあ、そうなると思ってたよ。さて、船長、俺の話を聞いてくれ。 お前は俺をきちんと処刑するために必死で生かしておいたんだろう？その点は感謝してるぜ。 ここでいきなり考えを変えてくれなんて言うのは、さすがに愚かだろうな？じゃあ、 もし俺から何か差し出すとしたらどうだ？取引ってやつさ、どうだい？\n";
			link.l1 = "何も言わんぞ、ポルトガル人。お前は海賊であり、ろくでなしだ。 ウィレムスタッドでその罪の報いを受けることになるぞ。";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "取引だと？何を差し出すつもりだ？";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "お前の取引なんざいらねえ、最初の港でさっさと消え失せろ。今日は運がいいな。";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "おい、俺の命を何度も助けてくれるなんて、理由がどうあれ感謝しないとな。ポルトガル人のバルトロメオは、 恩義ってやつをよく知ってるぜ。さて、よく聞け――お前と会う一月前、俺たちはカンパニーの船を拿捕したんだ。連中は最後の一人まで悪魔みたいに戦った。だが、 船倉にあったのは砲弾とネズミだけだったんだ\nうちの連中は不満だったが、俺は船長室で面白い箱と書類を見つけた。 あれはアマゾニアのどこかの鉱山からサンプルを運ぶ急使船だったんだ。純粋なダイヤとルビー――まさに大金だぜ！";
			link.l1 = "面白い獲物だな……なるほど、だからこそ商会があんたに興味を持つわけだ。だが、その話の肝心なところは何なんだ？";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "副長のバスケスとフランツ・ガルケは乗組員たちをしっかりまとめていたから、俺は一か八かの賭けに出ることにした。 二人には石を隠し、書類は焼き捨てた。オランダ野郎どもが乗り込みの時に艤装をひどく壊しやがったから、俺たちは 「アルバトロス」を北の小さな島の小さな入り江に入れざるを得なかった。乗組員全員がフリゲートの修理をしている間、 俺は一人でジャングルの奥へと進んだ\n石は埋めた。状況を考えれば船に積んだままじゃ危険すぎるからな。俺の計画は、 最初の港で愛すべき仲間たちからこっそり抜け出し、小舟を買うか盗むかして島に戻り、宝を回収して――それから……古い人生に別れを告げるってわけだ！ヨーロッパでまともな屋敷、美しい妻、あとは……まあ、想像がつくだろう……";
			link.l1 = "当ててやろうか、何かうまくいかなかったんだな。";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "すべてが台無しになった！くそったれな島は地元の人食いどもの巣だったんだ。俺が岸に戻った途端、奴らに襲われた。 俺たちは急いで出航するしかなかった、そのとき俺はやられたんだ。最初はただのかすり傷だと思ってた。\n数日後、俺は高熱で半死半生のまま寝込んでて、どうやら石のことを口走ったらしい。フランツとバスケスは、 俺が島に何か隠したと気づいたが、正確な場所までは知らなかった。あいつらは、 あの島をうろついてインディアンに撃たれ続けるのが気に入らなかったんだ。 だからあの野郎どもは俺を一番近い港まで引きずっていきやがった。オランダ人との戦いで船医が死んじまったから、 新しい医者が必要だったんだ。\nそうして俺はあの医者のところに転がり込んだ。奴らは俺を無理やり意識を戻して、 石のありかを吐かせるつもりだったんだ。その後はきっと俺を切り刻んで、 カニどもに俺のうまい肉を食わせるつもりだったんだろうよ。";
			link.l1 = "俺はあいつらを責める気はねえ――お前は自分の部下を騙そうとしてたんだろう。\nだからもう一度聞くが、なんでそんなことを俺に話すんだ？";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "こいつらは人間じゃねえ、信じてくれ。今ごろ全員、しかるべき場所――地獄にいるぜ、ハハッ！\n俺の自由と命の代わりに、オランダの財宝の正確な場所を教えてやるよ。";
			link.l1 = "いや、バート、お前の裏切りでお前の邪悪さには完全に確信を持った。ウィレムスタッドと正当な報いが待っているぞ。 取引などしない。";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "その宝石が本当に存在するなんて、俺が信じると思うのか？まあ、どうせ損はしねえしな……取引がこの話の始まりで、取引が終わりになるってわけだ。お前の条件、受けてやるぜ、ポルトガル人。";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "これは俺のささやかな感謝の気持ちだ。ええ、 バルトロメウ・ポルトガル人の皮がピカピカのペソでどれくらいの価値があるか知ってりゃな、はは！ お前の目的が実利的だったのは分かってるが、それでも全部に感謝するぜ、船長、ははは\nタークスだ、岸からそう遠くないジャングルさ。乾いて曲がった木を探せ――そこに一本だけある木だ。その近くに俺が宝箱を埋めた。だからシャベルを忘れるなよ。狩りを楽しめよ…";
			link.l1 = "よし、覚えておくぜ。今すぐロングボートに乗って俺の船から降りろ。さらばだ。";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "最後にもう一つだけだ、船長。野蛮人はまだたくさんいるだろうが、心配すべきは奴らだけじゃねえ。バスケスは『 アルバトロス』にはいなかったんだろ？血塗れのドンは頭が切れる野郎だ……首を吊るされるか、頭に鉛玉をぶち込まれるまで、背後には気をつけろよ。";
			link.l1 = "警告してくれて感謝するぜ、ポルトガル野郎。さて、もう俺の船から出て行ってくれねえか……俺の我慢を試すんじゃねえぞ。";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "おや、これは誰だ！船長 "+pchar.name+" 自分でな！飲みたいか？";
			link.l1 = "実は、また会えて嬉しいんだ。だが、マルティニークでお前に少し厳しくしすぎたかもしれねえな。";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "まあいいさ、船長！起きたことはもう仕方ねえ……でも正直に言うと、俺が追い出されても文句言えねえ理由を作っちまったんだ……だがよ、今日フィリップスバーグに誰が来てるか、あんた信じられねえぜ！\n";
			link.l1 = "「まさか、それは……」";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "いやいや、船長、ポルトガル人じゃねえよ。それに、また負傷した野郎でもねえ。もっとすげえんだ！ エルナンド・バスケスだ…あの“血塗られたドン”本人さ！ここ数日、地元の総督の客になってるんだぜ。";
			link.l1 = "バスケス？総督の客か？なるほどな。ユーゴ、もっと詳しく話せ、ここで一体何が起きてるんだ？";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "そうだな、俺はいろいろ知ってるぜ……だが今回の航海でまた無一文になっちまった。\nこの情報が欲しいなら、いくらかペソを払ってもらえねえか？";
			link.l1 = "ユーゴ、お前は相変わらずゆすり屋でろくでなしだな！言いたいことを言え、昔のよしみで五千ペソくれてやるよ。";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "どういうわけか、俺は驚いちゃいねえよ。ほら、１万ペソだ。その情報がそれだけの価値があるといいがな！";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "もっといい提案があるぜ。俺の船の仲間にならねえか？ お前は儲かる取引をまとめたり見つけたりする才能があると聞いてる。もう勇敢な戦士のふりをするのに疲れたなら、 俺の会計係の席が空いてるぜ、歓迎するぞ。";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "いや、船長、そんなやり方は通用しねえぞ！あんたはあの忌々しいポルトガル野郎と一緒に大金をせしめたはずだ。 だからそれが俺の取り分だと思え、欲張るんじゃねえ。1万5千コイン、1ペソたりともまけねえからな！";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "ああ、くたばれ、持っていけ！";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "「まあ、強欲は美徳って言うが……お前にはちょっと過ぎるんじゃねえか？」";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "これこそ俺の獲物だぜ！…聞けよ、バスケスは俺と同じ船に乗ってたが、俺が船賃のために甲板掃除してる間、 あいつは船室でのんびりしてやがった。おかげで顔を合わせることもほとんどなく、あいつも俺に気づかなかったんだ。 だが、俺はすぐにこの悪党の後を追い始めた…あいつには面白い出来事があったんだ。";
			link.l1 = "行けよ！あいつは総督の宮殿で何をしているんだ？";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "あまり詳しくは知らねえが、あいつが来てから数日間、守備隊は警戒態勢だったし、でっけえ軍艦が突然錨を上げて、 ものすごい勢いで出港したんだ。たしか北西に向かっていったと思うぜ。町中が噂話や憶測で持ちきりだったよ…\n";
			link.l1 = "あれが俺が遭遇した船だったのか！面白いな……話を逸らすな、ヒューゴ、続きを頼むぞ。";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "さて、さっきも言ったが、船は消えて、バスケスはうちの総督マルティン・トーマスの客みたいなもんになっちまった。\n時々町で見かけるが、いつも何人かの兵士と一緒にいるぜ。あれが護衛なのか、護送なのかは知らねえ、はは。\nだが、ドンについてもっと知りたきゃ、総督邸の連中に聞くしかねえな。";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "もしかしたらお前の言う通りかもしれねえ。だが、俺たちは約束しただろ？英雄ぶるなよ、 俺の船に行って戻るまで待ってろ。俺は親切な総督と話をつけてみるぜ。";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "ふむ、面白かったな。本当に助かったぜ、ヒューゴ。ラムを飲め、あとはお前の知ったことじゃねえ。";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "本気なのか、船長？どうかしてるんじゃねえか？俺の顔に銃を突きつけて追い払ったくせに、 今さらそんな提案を持ってくるのか？";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "そんなことは忘れてくれ、最近の俺はどうかしてたんだ、すまねえ。欲に目がくらんじまったんだろうな。ほら、1万ペソやるから、バスケスについて知ってることを教えてくれ、急いでるんだ。";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "その件については謝るべきかもしれねえな。お前は戦いじゃ情けねえが、金の扱いは悪くねえ。もう一度提案するぜ、 どうする？";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "何と言えばいいか……まあ、承知するぜ、だが自分の取り分をもらってからだ、船長。十分の一、覚えてるだろ？ あの悪党で二千手に入れたんだ、だから俺を仲間に入れたいなら、まず借りを返してもらわねえとな。十分の一だ、 文句はなしだぜ！";
			link.l1 = "お前は本当に詐欺師だな、ユーゴ。今はそんなに持ってないが、すぐ戻ってくる。ここで待ってろ。";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "お前のその商才で俺の期待に応えてくれるといいがな、ははっ！取り分を持っていけ！";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "決めるのはあんた次第だぜ、船長。俺はしばらくここにいる。気が変わったら戻ってきな。";
			link.l1 = "「いいだろう、Hugo。」";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "考えが変わったのかい、船長？じゃあ、金を待ってるぜ。";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "「コインを持っていけ、この野郎、ハハッ！」";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "まだそんな大金は持っていない。";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "ごきげんよう、船長。何かご用ですか？";
			link.l1 = "いやいや、私はただ待っているだけです。トマス旦那はいつお暇になりますか？私は謁見を待っているのです…そうです。教えてください、閣下は本当にあの有名な海賊エルナンド・バスケスを友人とお考えなのでしょうか？";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "心配いりません、旦那、もうすぐ彼は解放されるはずですし、もちろん違いますよ、旦那！ この盗賊は当局に投降しましたが、なぜか絞首刑にはなりませんでした。もしかすると、 昔の仲間を裏切って命を買ったのかもしれません……私にも分かりません。彼はここで数日間投獄されていました……あれは悪夢でしたよ、旦那！あの人間の皮を被った獣が我々の屋敷に住んでいたのですから！";
			link.l1 = "悪夢だぜ！あの化け物がトマス旦那に絞首台を免れるために何を話したっていうんだ？俺には想像もつかねえ！";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "俺も知らねえが、こっそり教えてやるよ、旦那様があんな客を追い出したとき、召使いたちはみんな喜んでたぜ…";
			link.l1 = "あいつを片付けたのか？ついに報いを受けたってわけか？";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "まだそうじゃねえ。数日前、あいつは軍のブリッグに乗せられてウィレムスタッドへ連れて行かれたんだ。分かるかい、 トマス旦那はその悪党に興味を失ったらしい。どうやら、あいつが旦那を騙そうとしたみたいだぜ。\nそれに、元船長のバルトロメウ・ポルトガル人も捕まったって話だ！考えてみろよ！ どうやら会社は二人まとめて吊るすつもりらしい。裁判は一ヶ月後だって噂だが、なんでそんなに待つんだろうな？";
			link.l1 = "ポルトガル人だと！？ふむ…付き合ってくれてありがとう、友よ…どうやらトマス旦那が今は手が空いたようだ、これで失礼するよ。";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "今やお前たちは二人とも死んだ……！";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "おお、船長、まさかお前に会うとは思わなかったぜ！だが、こんな血と騒ぎと銃声じゃ、友好的な訪問には見えねえな。 まさか花火で祝ってるってわけじゃねえだろうな、え？";
				link.l1 = "悪ふざけはやめろ、ポルトガル野郎。お前が俺から買った自由をどう使ってるか、気に入らねえんだよ。 せっかくお前の情けねえ尻を助けるために苦労したってのに、 別れた途端にそんな間抜けな捕まり方されちゃたまらねえだろうが！";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "退屈してたんだよ！だからここに遊びに来たのさ。ここは居心地いいかい、友よ！";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "気をつけろよ、友よ！ああ、手助けできなくて残念だ！";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "なるほど、貴族ってのは時に金じゃ動かねえってわけか？はは……気をつけろ、すぐ後ろだぞ！\n";
			link.l1 = "ああ、またこの忌々しい騒ぎかよ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "なるほど、貴族ってのは時に金に動じねえもんか。はっ……気をつけろ、すぐ後ろだぞ！";
			link.l1 = "ああ、またこんな血まみれの騒ぎかよ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "「だから言っただろ、この野郎は厄介だって！」";
			link.l1 = "危うく背中を撃たれるところだったぜ！どうやって奴は突破したんだ？";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "あいつがピッキングツールを持っているのを見たぜ、誰かが渡したんだろうな……あいつはいつも下層の連中と繋がりがあったからな。\nさて、船長、俺たちはここを離れるべきだと思うが、どうだ？";
			link.l1 = "そいつは驚いたぜ！よし、全衛兵が来る前に急ごう。お前の錠なんざ、すぐに壊してやる…";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "なあ、船長、この新鮮な空気……ダンジョンで何週間か過ごして、自分の船のボートが地元の巡回隊に見つかった後で、 初めてそのありがたみがわかるもんだぜ。俺はまだ、お前に助けてもらった借りがあるよな。";
			link.l1 = "必要ねえよ、ポルトガル野郎。俺は名誉ある騎士じゃねえ、ただ……自分が正しいと思うこと、やるべきことをやってるだけだ。";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "はは、それはまさに完璧な品だ！だが俺は譲らねえ、ほら、受け取ってくれ…これが牢屋で唯一隠し持っていたものだ…そう、その通りだ。これは俺のお守りさ。いつも航海で幸運をもたらしてくれた。お前は腕のいい水夫だし、 お前か航海士がきっと役立ててくれると俺は信じてるぜ。";
			link.l1 = "ああ、しかもその護符を持ったまま、運よくオランダ人の手にまっすぐ落ちたんだな。";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "おい！俺はまだ生きてるだろ？それに、もう牢屋にはいねえんだぜ。受け取ってくれ、船長、 今こそこの護符があんたの役に立つ時だ。改めて礼を言うぜ！";
			link.l1 = "じゃあな、ポルトガル野郎。頼むから絞首台には近づくなよ！俺の苦労のためにもな、ははっ！";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
