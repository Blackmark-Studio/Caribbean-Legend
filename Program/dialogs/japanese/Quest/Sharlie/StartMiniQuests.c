void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "今のところ何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "何かご入用ですか、旦那？";
			link.l1 = "あなたはグララム・ラヴォワで間違いありませんね？";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "誰が聞いてるんだ？ラムを飲んでる時に邪魔するな、旦那。今は話す気分じゃねえんだ。";
			link.l1 = "あまり時間は取らせません。サン・ピエールの商人に頼まれて来ました。あなたは彼の元従業員だったそうですね。 彼があなたを探していて……";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "ははっ、あいつが俺を探してるって！？あのケチ野郎がよく言うぜ！俺が一生あんなはした金で働くと思ってたのか？ カリブ一のドケチだぜ、あいつは！五年もこき使われて、もらったのはギリギリの給料だけだ！ちっ、 酒一杯買う金もねえよ！\nもう自分の品物は自分で数えさせりゃいい、俺は辞めたぜ。サン・ピエールであんなケチのために働く奴なんていねえよ、 間違いなくな。あいつの関心は一つ、自分の儲けを増やして、働く奴らにはできるだけ払わねえことさ。";
			link.l1 = "もうあいつの下で働くつもりはないんだろう？";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "いや、もし嘘をついたら神に打たれてもいい！俺はここル・フランソワで船が来るのを待って、 雇ってくれるなら会計士として乗り込むつもりだ。それが駄目なら、普通の水夫としてでもやっていくさ。 あの守銭奴の顔なんて二度と見たくもねえ。どうせ貧乏になるなら、せめて自由な身でいたいんだよ…";
			link.l1 = "承知しました、それだけ分かれば十分です。幸運を祈ります、グララム！";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "旦那、どいてくれ。邪魔だ！";
			link.l1 = "一つだけお聞きします、旦那。あなたはグララム・ラヴォワですか？";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "はっ！そうだ、俺だ。何の用だ？";
			link.l1 = "サン・ピエールの商人があんたを探してるぜ。昔、あいつの下で働いてたんじゃねえか？";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "ははっ！なんて冗談だ！それで王様は俺に何の用だ？最後の二週間分の給料でも払う気になったのか？ それとも樽の数を数えながら客をだますのに手こずってるのか、え？はははっ！";
			link.l1 = "彼はあなたを探して、なぜもう彼の店に働きに来なくなったのか理由をはっきりさせてほしいと頼まれたんだ。";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "なぜかって？あいつは血も涙もない守銭奴で、最悪の雇い主だからさ！俺は今やコースト同盟の一員、 もう奴隷じゃなく自由の身だ！見てみろよ、心から人生を楽しんでるぜ！\nもうすぐ出航して、バナナの箱じゃなくスペイン野郎から奪ったペソやドゥブロン銀貨を数えることになるんだ！ あのケチ野郎のことだが――俺の代わりを見つけられるとは思えねえな。サン・ピエールであいつのために働くほど馬鹿な奴はいねえよ。 島中の見習いどもにあいつの悪評を広めてやったからな、ははは！";
			link.l1 = "承知しました。それだけ分かれば十分です。幸運を祈ります、グララム！";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "どうなさいましたか？お手伝いできることはありますか？";
			link.l1 = "こんにちは。グララム・ラヴォワさんでいらっしゃいますか？";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "はい。ご用件は何ですか、旦那？";
			link.l1 = "サン・ピエールの商人があんたを探してるぜ。前にそいつの下で働いてたんじゃねえか？";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "まあ、好きに探させておけよ。俺はあいつに借りなんてねえしな。むしろ二週間分の給料をまだ払ってもらってねえが、 もう取り立てる気もねえ。あいつが自分の銅貨で喉を詰まらせりゃいいんだ。";
			link.l1 = "ふむ。つまり、もう彼のもとを完全に去ったということか？";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "全部その通りだぜ、旦那。俺の前の雇い主は、まさに聖書級のケチ野郎だったんだ。今じゃカリブの兄弟分、 仲間たちにも腕を認められてる。報酬は倍、しかもボーナス付きさ\nあの旦那が俺の代わりを見つけられるとは思えねえな。サン・ピエールの連中はあいつの強欲ぶりをよく知ってるし、 あんな奴のために働く馬鹿はいねえよ。";
			link.l1 = "わかった。それだけ聞ければ十分だ。幸運を祈るぜ、グララム！";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "こんにちは、旦那。出過ぎた真似をするつもりはありませんが、 私の立候補はご提案いただいたその役職にかなり適任だと存じます。";
			link.l1 = "こんにちは。さて、なぜそう思うのですか？";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "ごきげんよう、旦那！少し自己紹介をさせていただきます。";
			link.l1 = "お聞きしますよ。";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "ご機嫌よう、旦那。商人の職をお求めですか？";
			link.l1 = "ああ、そうだ。君のことを少し聞かせてくれないか？";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "私はフランシス・デュボワ船長の指揮下で四分士として仕えていたんだ。船長は俺の腕前にかなり満足していたが、 戦いで負傷して休養を余儀なくされた。今はもう大丈夫、体はすっかり元通りだが、 あの揺れる波を思い出すと気分が悪くなるんだ。いや、今の俺の唯一の望みは、しっかりした陸の上にいることだけさ\n（小声で）それに、もし俺を選んでくれたら、五百ペソと金のドブロン二十五枚を余分に払うぜ。";
			link.l1 = "なるほど。考えておくよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "俺は昔は行商人だったんだが、借金取りから逃げる羽目になって、商船の会計士として海に出たんだ。 運命に導かれてこの村にたどり着いた。まあ、船乗りの生活はあまり性に合わなかったし、 あんたの申し出を喜んで受けるぜ\n（小声で）それに、もし俺を選んでくれたら、五百ペソだけじゃなく、この重たい琥珀の包みも渡すぜ。";
			link.l1 = "なるほど。考えておくよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "私はグラスゴーの港の倉庫の一つで事務員をしていました。財産を求めてカリブにやって来て、 老後を立派に暮らせるだけの金を稼ぐことができました。しかし、海の旅にはもう飽きてしまい、 陸で静かな生活を送りたいのです\n（小声で）もし私を選んでくれたら、五百ペソに加えて、さらに二千五百ペソのボーナスを差し上げます。";
			link.l1 = "なるほど。考えておくよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "旦那、正しい選択をなさってください。そしてドゥブロンのこともお忘れなく……";
			link.l1 = "お前に有利な決定を下した。しっかりしろ。サン・ピエールへ行くぞ。";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "「まだ決めかねているんだ……」";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "私を選んでくださると嬉しいですわ、旦那。琥珀もまた、とても貴重で役に立つものですのよ……";
			link.l1 = "お前に有利な決定を下した。しっかりしろ。サン・ピエールへ行くぞ。";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "まだ決めかねているんだ……";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "商人は私の仕事に失望しません。\nそれと、あなたの報酬も忘れないでください。";
			link.l1 = "お前に有利な決定を下した。しっかりしろ。サン・ピエールへ行くぞ。";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "「まだ決めていないんだ……」";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "ちょっと荷物をまとめさせてくれ！酒場の入口で待ってるからな。";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "すぐに参ります、旦那！酒場の入口でお待ちしております。";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "俺の古いかばんを取って、酒場の入口で旦那を待ってるぜ！";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Back to Saint-Pierre...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "さて、これからここが私の職場になるんですか？ありがとうございます、旦那。私を選んでくださって。 こちらが約束通りの五百ペソと、上乗せのボーナスです。";
			link.l1 = "感謝いたします……あなたの雇い主をご紹介させていただきます。";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "旦那、すぐに私の船から降りていただきたい。\nこれから錨を上げて出航するのです！";
			link.l1 = "「よし……」";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "さて？お前は何者だ？";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "ラムを一杯やれ、水夫！ハハハ！俺のラガー船へようこそ。品物を受け取りに来たのか？";
			link.l1 = "ああ。他にここに来る理由があるか？";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "ラムを一杯やれ、水夫！ハッハッハ！俺のラガー船へようこそ。品物を取りに来たのか？";
				link.l1 = "ああ。他に俺がここに来る理由があるか？";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "おやおや、なんて青二才のろくでなしだ！おい野郎ども、こいつは新米みてえだな！海に放り込んじまおうぜ！\n";
				link.l1 = "「よっ！」";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "野郎ども！箱をランチに積み込め！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "ラム酒の箱はすべてお前のランチに積んである。\nポール・ル・フランソワはここから真南だ。\n急げよ、俺もそろそろ錨を上げる時間だ！";
			link.l1 = "時間を無駄にしないようにしよう、諸君！幸運を祈る！";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "お前もな、相棒……";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "お待ちしておりました、旦那。すべてうまくいきましたか？箱は持ってきましたか？";
			link.l1 = "すべて見事にうまくいった。ラム酒の箱は発艇に積んである。";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "よし。ここからは俺たちが引き受ける。お前はサン・ピエールの酒場へ行って、報酬を受け取れ。 夜のジャングルでは油断せず、用心しろよ。";
			link.l1 = "ごきげんよう、諸君。";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "こんにちは、旦那！申し上げますが、あなたは普段この植民地をうろついているみすぼらしい悪党どもには見えませんね。 服装からして、ずいぶん遠くから来られたのでしょう……ヨーロッパからいらしたのですか？";
			link.l1 = "まさにその通りです、旦那。 "+GetFullName(pchar)+"、お仕えいたします。ご用件は何でしょうか？";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "自己紹介させていただきます—— "+GetFullName(npchar)+"……数年前にフランスからこの忌まわしい場所へやって来ました。しかし、それは今は関係ありません。実は、 あなたにとても繊細なお願いがございます\nどうかご理解ください。もしあなたが紳士であると確信していなければ、 このような頼みごとを決してお願いしませんでした。";
			link.l1 = "どうぞ、ご用件をお聞かせください、旦那。私にできることでしたら、もちろんお力になりましょう。";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "それは嬉しい知らせです、ド・モール旦那。さて、どう言えばよいか……この町には娼館がありましてな。最近、そこに新しい娘が現れたのです。若くて、色白で、金髪で、驚くほど美しい！ 私は何週間も彼女を見てきて……どうしても彼女と二人きりで過ごしたいという強い欲望が湧いてきました\nしかし、私の地位や身分では、そういう場所に行くのは……都合が悪いのです。噂になったら大変でしょう！\nだからこそ、あなたにお願いしたいのです。率直に言えば、あなたはこの島の新参者で、誰もあなたのことを知らず、 あなたが何をしても……まだ誰も気にしません。どうか、私のために一肌脱いでいただけませんか、旦那。";
			link.l1 = "あなたの言いたいことは分かってきた気がする。";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "ご配慮に感謝します、"+pchar.lastname+"旦那。私からあの娘のもとへ行くことはできませんので、娘のほうから私の家に来てもらう必要があります。そこで、 あなたに頼みたいのは、娼館へ行き、マダムと交渉して、あの金髪の娘が一晩だけ私の家に“出張”できるよう取り計らっていただくことです。\nオーロラは断らないでしょう。彼女はそういうサービスで有名ですが、いつも少し高くつきます。その後、 あなたが娘を私の家まで連れてきてください。報酬として六千ペソを差し上げます。オーロラは通常、娘を家に呼ぶ場合、 一晩で三千から三千五百ペソを取ります。余った分は、あなたの手間賃としてお受け取りください。";
			link.l1 = "そんなに難しそうじゃないな。俺にできるぜ。";
			link.l1.go = "GigoloMan_4";
			link.l2 = "旦那、私もあなたと同じくらい紳士としての名誉を大切にしております。どうかご容赦ください、 しかしご要望にはお応えできません。お断りいたします。\n酒場へ行って、宿屋の主人に仕事がないか確かめてみるべきでしょう。";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "それは本当に嬉しい知らせだ。さて、よく聞いてくれ、あの娘の名前はルシールだ。俺の頼みは、夜になってから、 できれば午後十一時以降に、余計な野次馬の目を避けるため、俺の家まで彼女を連れてきてほしいということだ。 ドアをノックしてくれれば、俺が開ける。\n俺の家は総督邸の左手、建物の裏側に面している赤い屋根の二階建ての館だ。すぐ見つかるはずだし、近くに店もある。 実は今から家に向かうところだから、よかったら一緒に来て、どんな家か、どこにあるか確かめておくといい。 夜に迷わないためにな。\nさて、本題だが――ほら、六千ペソ受け取れ。約束の時間に待っているぞ！";
			link.l1 = "取引成立だ。お前の金髪のリュシールは今夜、お前の家の前に現れるぜ。";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "ごきげんよう、旦那。まあ、今夜私を雇ったのはあなたかしら？あらあら、 こんなにハンサムで身なりの良い紳士にお相手してもらえるなんて、私って本当に運がいいわ。 港から上がってくるタールと汗臭い荒くれ者たちとは大違いですもの…";
				link.l1 = "申し訳ないが、今夜は無理なんだ、ルシール。私は親友の代理で来ているんだよ。 彼は実に複雑な事情で家を出られないから、君を彼のもとへ連れて行くことになっている。\nまあ、気を悪くしないでくれ。彼は優しい男で、君のこともとても気に入っているんだ。 きっと最後には君も満足すると思うよ。";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "うーん……君の言う通りだよ、愛しい人。行こうか？";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "旦那、夜にあなたと一緒にぶらぶら歩き回るわけにはいきませんの。早くお友達のお宅に連れていってくださらないと、 すぐにマダムのところへ戻りますわよ。そうしたらあなたのお金は無駄になりますわ。";
				link.l1 = "わかった、ついて来い！";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "残念ですわ……私はあなたのこと、すぐに気に入りましたのに、旦那。今夜ご一緒できたら素敵だったのに……また今度、ですわね。行きましょうか？";
			link.l1 = "ああ、俺について来い！";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "なんて立派な屋敷だ。ここがその場所か？";
			link.l1 = "はい。入ってくれ。怖がるな、俺の友はいい奴だ。";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "私を侮らないでください、私は怖くありませんよ、旦那。自分の身の守り方は心得ています。さて、いずれ機会があれば、 マダムに私と一晩過ごす代金を払っていただけませんか？きっと人生最高の夜にしてみせますよ！";
			link.l1 = "何が起きてもおかしくないさ、ルシール。また会うこともあるかもな。じゃあな！";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "何だこれは！？お前は誰だ？ここで何の用だ？さあ、さっさと出て行け！";
			link.l1 = "「お前はあまり礼儀正しくないな、旦那。」";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "聞けよ、坊主、俺は礼儀なんざ教わっちゃいねえし、読み書きだってできねえが、カトラスでてめえの頭をかち割るのは、 娼婦がひっくり返るくらい簡単なんだぜ。\nそれにな、もし今すぐここから出ていかねえなら、死体になって運び出されることになるって、俺の命にかけて誓うぜ。 わかったか？";
			link.l1 = "いいや、今度は俺の話を聞け、このろくでなし。お前の企みはもうバレてるんだ。あの男は生かしておく必要がある、 だから武器を捨てて逃げろ。俺のすぐ後ろのジャングルにはフランス兵の小隊が控えてるんだ。素早く逃げれば、 みじめな命くらいは助かるかもしれねえぞ。";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "わかった、わかった、落ち着け。俺はもう行くよ。";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "な、なんだと？ bleffしてるだけだろ、相棒！野郎ども、やっちまえ、武器を取れ！\n";
			link.l1 = "それなら自業自得だ、構えろ！";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "神に感謝を！ああ、お前はフランス人か？くそっ、あの野郎どもを見事に追い払ったな。だが、 俺が簡単に降参すると思うなよ、スペイン人の戦い方を見せてやる！サンティアゴ！\n";
			link.l1 = "「いや、待って、お願い！」";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "フランス人に捕まるくらいなら死んだほうがマシだ。お前が戦っている間に、死体の一つからカットラスを拝借した……今からスペイン風のクアドリーユを踊らせてやるぜ！";
			link.l1 = "お前らスペイン人はラバみてえに頑固だな！";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "くそっ……お前の勝ちだ。降参する、くたばれフランス野郎。好きにしろ。";
			link.l1 = "剣を収めろ、頑固なカスティーリャ人め！俺はお前に死んでほしくもねえし、牢屋に送るつもりもねえんだ！";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "それじゃあ、何をしているんだ？なぜ海賊たちを殺した？それに、お前の兵士たちはどこにいるんだ？";
			link.l1 = "兵士はいない。あの悪党どもを騙そうとしたが、ご覧の通り、うまくいかなかった。私は一人でここにいる、 君の古い友人の頼みでな。彼の名は\n "+pchar.questTemp.Sharlie.Captive.Name+"、あいつはサン・ピエールの銀行家だ。";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"？その名前の者は知らないな……";
			link.l1 = "私はあなたやあなたの捕縛について何も知りませんでした。あなたがイギリス船に移送されたことも、 彼から聞いたのです。私の任務はあなたを彼のもとへ届けること、それを果たすと誓いました！\nさあ、生きたければ私についてきてください。";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "どうせ俺に選択肢なんてねえしな……あんたの銀行家だって、イギリス野郎とあのひどい料理よりはマシだろうさ……";
			link.l1 = "やっと賢い決断をしたな。もう話は十分だ、これからサン・ピエールへ向かうぞ。俺のそばを離れるな、 勝手な行動はするなよ。逃げたら、また捕まえて半殺しにしてやるからな。";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "ご用件は何ですか、旦那？話している暇はありませんので、手短にお願いします。";
			link.l1 = "お前はプロスペル・トルバルだろう？";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "ああ、私がそうです。しかし、あなたの方が私より有利な立場ですね。どちら様で、 一体何の用なのか教えていただけますか。";
			link.l1 = "私の名前は "+GetFullName(pchar)+"。私はあなたのもとへ派遣されてきた "+GetFullName(characterFromId("Fortfrance_portman"))+"、港湾長だ。あなたが至急助けを必要としていると言っていた…";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "なんてこった、そうだよ！あの司令官の野郎、俺の訴えなんて耳も貸しやがらねえ！怠け者か臆病者か、 どっちかだろうな。お前、本当に俺を助けに来てくれたのか？もしそうなら、ただでは済ませねえぞ！\n";
			link.l1 = "ああ、プロスペール。何があったのか、そして私がどう助ければいいのか教えてくれ。 娘さんが行方不明になったと聞いたが……";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "はい、私の愛しい娘セレーヌが二日前から行方不明なのです。ここからそう遠くない砦へ散歩に出かけたのですが、 戻ってこなかったので、私自身が砦まで行ってみたところ、兵士たちは「彼女は一度も来ていない」と言うのです！\nそれで帰り道、私は二人の野蛮なインディアンに襲われました！やつらはこん棒を振りかざして飛びかかってきて、 私を殴ろうとしたのです。\nですが、私はただの子猫じゃありませんから、一人の顔面にパンチを食らわせ、その隙にピストルを抜いて撃ちました。 外しましたが、奴らは怯えて逃げていきました。私はなんとか街の門までたどり着き、衛兵に襲撃のことを伝えました。 衛兵たちはすぐにジャングルへ向かいましたが、野蛮人たちはすでに姿を消していました。\n私は、あいつらがセレーヌ失踪の犯人だと確信しています。それに加えて、先週だけでさらに二人――セザール・ブランシェとジルベール・クルシーも行方不明になっています！一人は入り江へ、 もう一人はル・フランソワへ向かったきり、戻ってきていません。";
			link.l1 = "つまり、インディアンたちが街の門のすぐそばで住民を襲っているってことか？信じられないほど大胆だな……";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "その間、私は自分でジャングルに出て彼女を探し、街の北にある洞窟を見つけた。 中であの野郎どもがうずくまっていたんだ。入口には何人かインディオがいたが、中にも何人かいるに違いない\n女の子の叫び声が聞こえた……あれは私のセレーヌだ、間違いない、あの声は彼女だ！その場で飛び込まなかったのは、全て自制心のおかげだった――分が悪すぎたし、奴らに殺されていただろう。私が死んだら彼女を助けられないからな。";
			link.l1 = "「しかし一体なぜ奴らは攻撃して、町の人々を捕虜にしているんだ？」";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "わからねえな……海賊か奴隷商人に売るつもりかもな？それとも、そのまま生きたまま食っちまうかも。なんせ奴らは野蛮人だからな。";
			link.l1 = "天の神よ、あいつらは人食いなのか？ヨーロッパで子供を脅かすための作り話だと思っていたのに……";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "話か？まあな、あんたみたいな奴もそう思ってたが、カリブの連中に火あぶりにされて食われたんだよ……だから俺はすぐに司令官のところへ行って、セレーヌを救うための討伐隊を要請したんだ。だが断られた！ 女が行方不明になる時は、インディアンじゃなくて男と駆け落ちしたんだろうってさ。 地元の干し草小屋でも探せって言われたよ\nそれに、他の二人の失踪については……一人は密輸の疑いがあるし、もう一人はル・フランソワの酒場で酒浸りになって死にかけてるんじゃないかってさ。結局、 何も得られず、自分で動くしかないと決めたんだ。";
			link.l1 = "何をするつもりだ？";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "俺があそこに行って、あの赤い野郎どもを一人残らずぶっ殺してやる。セレーヌがまだ生きていることを祈るしかねえ。 見ての通り、マスケット銃を買った――しかも撃ち方も心得てる。かなりの金を払ったが、そんなことはどうでもいい\nお前が一緒に来てくれれば、俺の任務はずっと楽になる。お前が俺が弾を込めている間、背中を守ってくれれば、 二人であの野蛮人どもを簡単に片付けられるはずだ。俺と一緒に娘を救いに行ってくれるか？";
			link.l1 = "もちろんだ！名誉の問題だぜ！野蛮人の刃で娘が死ぬのを黙って見ていられるかよ。";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "ふむ。そうだな、司令官の言葉も一理ある気がする。まずは彼の助言に従ってみるか？";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "旦那、あなたの剣はどこですか？";
			link.l1 = "どうやら失くしてしまったようだ。";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "それでは全く話になりませんわ。夕方までお待ちいたしますから、総督の足元にひれ伏して、 お助けを乞うことをお勧めしますわ。";
			link.l1 = "「奴の足元にひれ伏せってか？まあ、好きにしな…」";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "さて、旦那？武器は手に入れたか？";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "まだです、もう少しお待ちください…";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "了解だ。手伝う準備はできてるぜ！";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "なんてこった、逃げるのか？違う！さっさとここから失せろ！腰抜けめ！";
			link.l1 = "おいおい、落ち着けよ、このお馬鹿さん！俺は外に出て、 サン・ピエールの通りで困ってる貴族がいないか見てくるとするか。";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "この町に少なくとも一人は勇敢な男がいて嬉しいよ。\nほら、この三つの小瓶を持っていきなさい。\nこれは体に良い薬草だ。うちの薬草師から買ったんだ。\n戦いで大いに役立つはずだよ。";
			link.l1 = "お前はどうなんだ？";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "心配するな、まだあるぜ。準備はいいか？";
			link.l1 = "ああ、時間を無駄にせず行こう。進め！";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "「もうすぐ配置につくぞ」 "+pchar.name+"。この曲がり角の先が洞窟の入口だ。もっと近くに来い、計画を教えてやる。";
			link.l1 = "聞いてるぞ、プロスぺール。";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "この重い火縄銃で狙いを定めるには時間が必要だ、だが時間を稼いでくれれば外さないさ。\nもし白兵戦になったら、射撃の援護は期待しないでくれ、銃身を棍棒代わりにして敵を追い払うしかない。\nこの戦いはお前の剣の腕にかかってるぜ。";
			link.l1 = "何が言いたいんだ？";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "お前がやるべきことは、あいつらの注意を引きつけてくれることだけだ。俺は動きながら撃てねえから、 一か所に陣取るぜ。洞窟の入り口付近に三人の野郎がいる。お前は剣を抜いてできるだけ素早く突っ込め\n一人を斬りつけて、俺から引き離すように追わせろ。三人ともお前に集中すれば、俺が鳥を撃つみたいに撃ち倒してやる。 その間、お前は受け流して避けてくれ。だが、あの野蛮人どもが俺に襲いかかってきたら、もう終わりだ。準備はいいか？ ";
			link.l1 = "剣を扱うのはこれが初めてじゃないさ。こんな野蛮人ども、脅威でもなんでもない。";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "はっ！俺のことは心配するな。ル・マンで狩りをするのと同じさ！ただ、間違って俺の背中を撃たないでくれよ！\n";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "先に行け、俺はすぐ後ろにいる。\n忘れるな、奴らを俺に近づけちゃいけねえぞ！";
			link.l1 = "覚えている、行こう。進め！";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "それじゃあ、戦闘の準備をしろ。先に行け、俺もすぐ後ろに続く。忘れるな、奴らを俺に近づけさせるなよ！";
			link.l1 = "覚えている。できる限りのことはやる。進め！";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "「よくやった」 "+pchar.name+"！この異教の野蛮人どもはもう殺させねえ。さて、本番は洞窟だ。中には三人か四人いると思うが、確信はない。 よく聞け\n十年前、俺はそこにいた。洞窟の中には狭い通路がある。その先に小さな洞窟があって、 壁で仕切られてるが真ん中に穴が空いてるんだ。前と同じ作戦でいくぞ。俺は入口の近くに立つから、お前は突入しろ\n奴らを挑発して、全員まとめて相手しようとするな。俺に攻撃させないようにしてくれ。 さっき言った通路のところで構えろ、狭いから一度に一人か二人しかかかってこられねえ\n俺はお前の肩越しに撃つ。準備はいいか？";
			link.l1 = "進め！この野蛮人どもの巣を叩き潰すぞ！";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "娘が生きている！神に感謝だ！間に合ってここに来られたぞ。 "+pchar.name+"……あなたには借りができました、旦那。あなたは勇敢で腕の立つ戦士ですね！";
			link.l1 = "ハッピーエンドになってよかったよ、プロスぺル。インディアンどもを片付けるのは、 まったく血なまぐさい仕事だったな。";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "「改めて心より感謝いたします」 "+pchar.name+"！さあ、町へ戻ろう。私の娘の命は金では計れぬほど尊いが、 あなたには残りの貯金を差し上げて感謝の気持ちを伝えたい。サン・ピエールに着き次第、喜んでお渡しするよ。 断るなんて考えもしないでくれ！";
			link.l1 = "断らないよ、プロスペル。もっとも、君を助けた動機は金じゃなかったけどな。";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "あなたは真のキリスト教騎士だ "+pchar.name+"！さあ、ここでぐずぐずしてる場合じゃねえ。さっさと家に帰るぞ！";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "着きましたね、シャルル。改めて助けてくれて感謝します。 このささやかなペソと金のドゥブロンをお礼の言葉と共に渡します。ドゥブロンは無駄遣いせず、 特別な時のために取っておくことを勧めます。あなたが私にしてくれたことに比べれば大した額ではありませんが、 心からの気持ちです。それから、このお守りも受け取ってください。 "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "ありがとうございます！では、ごきげんよう、プロスパー。あなたと愛しい娘さんの幸せをお祈りします！";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "ああ、あんたみたいな旦那なら、あの娘も幸せになれるだろうよ。あの子はいつも、 町中のヒョロヒョロ足でアゴのない貴族気取りに追い回されてばかりだったんだ。まったく、 そいつらが全員どこかに消えちまったのは残念……いや、むしろせいせいしたぜ。幸運を祈るぜ、シャルル！";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "ああ！神よ、お助けください！（泣きながら）あなたには…ここで起きている恐ろしさなんて想像もできないでしょう！こ、このインディアンたちが俺たちをここに引きずってきて、 殺して食うつもりなんだ！セザール・ブランシェもここにいた…野蛮人どもが彼を連れていった…何かひどい悪魔の儀式をやって、それから…主よ、とても口にできません！次は俺の番だったんだ！明日、俺を殺すつもりだったんだ…！";
			link.l1 = "落ち着いてくれ、セリーヌ。すべて終わったんだ。あの野郎どもは報いを受けて、もう誰も傷つけることはないさ。";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "ギルベール・クルシーもここにいるぞ。あそこだ……彼は、えっと……まだ回復していないんだ。彼と話してくれ……それから、さっさとここを出よう！";
			link.l1 = "よしよし、もう大丈夫だ、娘さん。もう泣かなくていい。すべてうまくいくさ。君には素晴らしい父上がいるじゃないか。 誰にも君を傷つけさせたりしないよ……外に出ておいで、俺が……ええと……ギルバートをここから連れ出して、あとで君のところに行くからな。";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "神様と聖母マリア様が私の祈りを聞き届けてくださった！私たちを助けに来てくれたのですか？";
			link.l1 = "お前……名前はセリーヌだろう？";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "はい……（泣きながら）あなたには、ここで起きている恐怖が想像もできないでしょう！こ、 このインディオたちが俺たちをここに引きずってきて、殺して食おうとしてるんだ！セザール・ブランシェもここにいた……奴らは彼を連れていった……悪魔のような儀式をやって、それから……神よ、とても口にできない！次は俺の番なんだ！明日、俺を殺すつもりなんだよ……！";
			link.l1 = "落ち着け、お嬢ちゃん……すまないが、悪い知らせを持ってきたんだ。私は君のお父さんと一緒にここへ来た。君のために戦っている最中、 外であの赤い肌の野蛮人どもに殺されてしまったんだ。君を救うために命を捧げたんだよ。";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "「何だって！？父上が……ああ、神よ！私……私……（すすり泣き）」";
			link.l1 = "お悔やみ申し上げます、セリーヌ。ここにあなたと一緒にいる他の誰かがいるのですね？";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "（涙ながらに）はい……ジルベール・クルシーです。あそこにいます……まだ回復していません。彼に話しかけてください……それから急いでここを出ましょう！";
			link.l1 = "ええ、もちろんです。ここで立ち止まっている暇はありません。";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "父上……私の哀れで大切な父上！ああ、旦那、私を助けてくださったことに、まだお礼も申し上げておりません……";
			link.l1 = "セリーナ、君とギルバートがあの洞窟から生きて戻れたことが本当に嬉しいよ。 君のお父上の英雄的な最期は決して無駄ではなかった。";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "（泣きながら）お願いです、旦那、私たちを町まで連れて行ってください。兵士たちを呼びに行かなくてはなりません。 父の遺体を迎えに来てもらい、きちんとしたキリスト教の埋葬をしてあげたいのです…";
			link.l1 = "もちろん、セリーヌ。ついて来て！";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "ありがとうございます、旦那、私の哀れな父に付き添ってくださって……。私を確実な死から救ってくださって、本当に感謝しています。わ、私は……。これ、このドゥブロン金貨の袋を受け取ってください。家で父の箱の中に見つけたものです。どうか、 断るなんて考えないでください！";
			link.l1 = "ありがとう、セリーヌ。君を救うことができて本当に良かったよ。\nそして、お父上を亡くされたこと、心よりお悔やみ申し上げます。";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "あなたは高貴な方です、旦那。決してあなたのことは忘れません。さようなら！";
			link.l1 = "さらばだ、セリーヌ。";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "ああ、主よ、本当にすべてが終わったのでしょうか？信じられません……あなたは私もセリーヌも救ってくれました。もしあなたがいなければ、 哀れなセザールに降りかかった運命が明日には彼女にも訪れ、数日後には私にも同じ運命が待っていたことでしょう。";
			link.l1 = "「このインディアンたち、本当に人食いなのか！？」";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "疑ってるのか？もし肝が据わってるなら、あいつらの焚き火の灰を覗いてみな。可哀想なセザール爺さんがそこにいるぜ。 今じゃ噛み砕かれた骨だけだがな…";
			link.l1 = "聖体拝領……いや、遠慮しておくよ。私はつい最近ヨーロッパからここに来たばかりで、 こんな忌まわしく邪悪なことが今も地上で行われているなんて想像もできなかったよ。";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "カリブでは奇妙なことがたくさん起きるんだ、旧世界では噂でしか聞いたことのないようなことが……インディアンの呪医や魔法、シャーマン、そして秘密の儀式。ここに長くいれば、 あらゆる悪魔の仕業を目の当たりにするだろう。しかし、失礼したな、君に助けてもらった礼をまだ言っていなかった――まだ動揺しているんだ\n君は私の命を救ってくれた。感謝の気持ちは言葉だけでなく、金でも示そう。セリーヌと私を街まで護衛してくれ。 そこで改めて、ふさわしい礼をさせてもらう、旦那。";
			link.l1 = "よし。外に出てくれ。俺はまずここを見て回る。";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "改めて、私を救ってくださったことに深く感謝申し上げます、旦那！約束通り、言葉だけでなく、 銀ペソと金ドゥブロンという形でも感謝の気持ちをお渡しいたします。";
			link.l1 = "すべてがうまくいって本当に嬉しいよ、Gilbert。";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "こんなに嬉しいなんて、自分でも想像できません！改めて感謝いたします、それでは失礼いたします、旦那。";
			link.l1 = "幸運を祈るぜ、ギルベール！ところで、サン・ピエールで他に助けが必要な奴を知ってるか？";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "私には分かりませんが……旦那、通りにいる市民たちに聞いてみてはいかがですか。\n普通の町人や裕福な者でも大した話はないでしょうが、金持ちの貴族たちなら……何か仕事を持っているかもしれませんよ。";
			link.l1 = "了解だ、ギルベール、ありがとう。またな！";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"聞きなさい、君。私はこの街の法を守る市民だ。強盗のように刃物をむき出しで歩き回るのはやめてもらいたい。","旦那、どうかご理解ください、法は明白です：市壁内で抜き身の武器を持ち歩くことは許されておりません。");
			link.l1 = LinkRandPhrase("「よし。」","かしこまりました。","お望みのままに……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
