// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か欲しいのか？";
			link.l1 = "いや、なんでもねえよ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "おいおい、見ろよ、野郎ども！誰が俺たちのところに来たと思う？人の箱をあさる泥棒じゃねえか！こっちに来い！ それと、お前、しらばっくれたり刃物を抜いたりするんじゃねえぞ――この距離じゃ外さねえからな……チャドがきっとお前に会えて喜ぶぜ！\n";
			link.l1 = "でも俺は……俺は今着いたばかりなんだ！";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "その通りだ、ははっ！お前さん、とんでもねえ厄介ごとに首を突っ込んじまったな……もう逃げられねえぜ。さあ、武器をよこして俺について来い！『タルタロス』の檻は、 ずっとお前みてえな泥棒を待ってたんだ！";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Few hours later...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "ここで何か盗もうなんて考えるなよ。俺が見張ってるからな。";
			link.l1 = "どういたしまして。";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "チャドに言われたことをやれ。あまりしゃべるなよ！";
			link.l1 = "ああ、今向かっているところだ…";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "おい！そこで何してやがるんだ？この野郎！もう終わりだぜ！";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "おい、てめえ、ここで何してやがるんだ、くそっ！？バルビエはどこだ？";
			link.l1 = "俺たちの仲間アドルフォは……具合が悪いんだ。\n会合には来られなかったから、しばらく彼の船室でお前を待っててくれって頼まれたんだよ。";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "おい、てめえ、こんなところで何してやがるんだ、くそったれ！？";
			link.l1 = "俺たちの仲間アドルフォは……具合が悪いんだ。\n会合には来られなかったから、代わりに俺に来てくれって頼まれたんだよ。\nまあ、そういうことさ。";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "妙だな……今朝は元気だったのに、今は病気だなんて。";
			link.l1 = "まあ、物事ってそういうもんだろう。突然の熱病の発作でな…";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "ああ、お前の面が気に入らねえな。嘘ついてやがる。バルビエがこんな大事な話を他の奴に任せるわけねえだろ。言え、 この野郎、お前は何者だ、あいつに何をした？";
			link.l1 = "あんたも大した見た目じゃねえな。バルビエが病気だってもう言っただろ。頭が鈍いのか、 それとももう一度言わなきゃわからねえのか？奴があんたに鍵を渡すはずだったんだが…";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "くそっ！俺を追い詰めやがったな……";
			link.l1 = "ああ、クズども！あの娘には指一本触れさせねえ！死ぬ覚悟をしろ！";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "あなたは "+GetFullName(pchar)+"?";
			link.l1 = "ああ、俺だ。どうしたんだ？";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "シャークが俺を寄越したんだ。できるだけ早く会いに来てほしいってさ。お前にとって大事な話があるらしいぜ。";
			link.l1 = "「そんなに急いでどうしたんだ？……わかったよ、すぐに『サン・アグスティン』へ行く。」";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "あなたは "+GetFullName(pchar)+"?";
			link.l1 = "ああ、俺だ。どうしたんだ？";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "ああ、探し回って疲れたよ……シャークとレイトン・デクスターが、すぐに会いに来いってさ。とても重要な用件だから、急いでくれ。";
				link.l1 = "そうか？よし、俺はすぐに『サン・アグスティン』へ行くぜ。";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "ああ、探し回って疲れたぜ……レイトン・デクスター提督がすぐに会いに来いとお前に言ってる。とても重要な用件だ、急げよ。";
				link.l1 = "提督？";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "ああ。副官だった彼は、シャークの死後、俺たちの提督になったんだ。";
			link.l1 = "なるほど。よし、すぐに『サン・アグスティン』へ向かう。";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ああ、ここにいたか……思い出したぞ、お前はチミセットと最後に話した男だな。奴を殺したのか？";
				link.l1 = "ふざけるな！俺じゃないことはお前が一番よく知ってるだろう。犯人が誰かも、お前は分かってるはずだ。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "ええ、ここで一日中過ごすのは退屈だぜ！ラム酒とカードでも持ってきてくれりゃ、相棒、 ちょっと賭けでもできたのにな…";
				link.l1 = "悪いな、相棒、今はそんな暇ねえんだ。また後でな。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "ああ、いくつか推測はあるが、確かな証拠はねえ。黒人の死を見た者はいないんだ。島中で噂が飛び交っててな、 俺たちシャークの連中がやったとか、提督の命令でどこかの新参者がやったとか言われてる。分かるか？ だから今は特にリヴァドスには近づくな。あいつら、今は怒り心頭だぜ。";
			link.l1 = "わかった。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "ええ、ここで一日中じっとしてるのは退屈だぜ！ラム酒とカードでも持ってきてくれりゃ、相棒、 ちょっと賭け事でもできたのにな…";
			link.l1 = "悪いな、相棒、今はそんな暇ねえんだ。また後でな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "何の用だ、相棒？";
			link.l1 = "ふむ。それで、ここに何の用だ？アクセルはどこにいる？";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "アクセルは忙しいんだ。今はドナルド・グリーンスペンと会議中で、今日一日ずっと一緒にいるんだよ。\nだから、何か買いたいなら明日の朝にまた来てくれ。\nそれに、店番は俺がしてるから、盗みなんて考えるなよ……";
			link.l1 = "なるほど。それで、なぜ今日やるんだ？まあいい、明日の朝ここに来るとしよう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("もう全部話しただろう。明日また来い。","邪魔すんな、相棒。消えな！","俺を怒らせるんじゃねえぞ、この野郎！","消えろ！！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("いいだろう。","わかった、わかった。","黙れ……","「何だって！？」",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "何の用だ、旦那？";
			link.l1 = "うむ……申し訳ありません、お嬢様。無礼と失礼をお許しください。でも、ひとつお聞きしたいことがございます。 オーレ・クリスチャンセンという男をご存知ですか？";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "今言ったことをもう一度言ってくれ……オーレ・クリスチャンセンだと？オーレ！？";
			link.l1 = "ああ。あいつは髪の色が変わってるから「白い坊や」とも呼ばれてるんだ。知ってるのか？";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "俺があいつを知ってるかって？！あいつは俺の息子だ、もう十年も行方不明なんだぞ！旦那、 あいつの居場所を知ってるのか？早く教えてくれ、あいつに何があったんだ！？";
			link.l1 = "落ち着いてください、奥様、そんなに心配なさらないで。彼は無事です。私の船にいます。 あとは上陸してここに来るだけです。";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "ああ……ついに主が私の祈りを聞き届けてくださったのですね！彼が行方不明になった時、私がどれほど心配したか、 あなたには想像もつかないでしょう！それも、すべて私の責任、私だけの過ちなのです！どこで彼を見つけたのですか？ 彼は普通の子供ではありません……まあ、あなたも何のことかお分かりでしょう。";
			link.l1 = "そうだ。ああ、あいつは特別な奴さ。そして、全然変わっちゃいねえ。まるで子供のままだ。 俺はある島であいつを見つけたんだ。偶然の出会いだった。あいつは俺に白いビーズをくれって頼んできて……くそっ！……真珠のことだった。";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "真珠だって？ああ、神よ！真珠のせいでうちの息子はいなくなったんだ！全部あの忌々しい首飾りのせいさ！";
			link.l1 = "オーレが……あんたの真珠のネックレスを壊したせいで家を出たって本当かい？……落ち着いてください、お嬢さん、泣かないで！";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "そう、本当よ。オーレが桟橋で私の首飾りを引きちぎって、真珠が全部水の中に落ちたの。私はあいつを散々罵ったわ、 それで亡くなった夫が……オーレを罰したの。翌日、オーレは姿を消したのよ。私がどれだけ自分を責めたか、あなたには想像もできないわ！";
			link.l1 = "オーレは何年も真珠を集めてきたんだ。彼はそれを「白いビーズ」と呼んでいる。全部お前のために集めて、 俺にお前のところへ連れて行ってくれと頼んできた。赤い屋根の家しか手がかりがなかったけど、 ついにお前を見つけることができたぜ。";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "真珠を集めてるって！？ああ、神よ！かわいそうな息子に本当に申し訳ない気持ちだわ！あたし…それに、あの子は真珠を集めていたのね！ああ！";
			link.l1 = "奥様、お坊ちゃんをお呼びした方がよろしいでしょうか。あの子はあなたに会いたくてたまらなかったんですよ。 真珠を見せれば、きっとあなたが喜ぶと言っていました。でも、私が思うに、 あなたが喜ぶのは真珠のせいじゃないでしょうね…";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "旦那……お願いできませんか。私のオーレを連れてきてください。抱きしめて、許しを乞いたいのです……";
			link.l1 = "かしこまりました、お嬢様。すぐに彼をここへ連れてまいります。";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "さて、旦那、こちらがあなたの息子、オーレ・クリスチャンセンです。彼のことを覚えていますか？";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "旦那……すみません、お名前を伺っていませんでした…… "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+"、旦那。船長 "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "船長、私の息子のことでどれほど感謝しているか、あなたには想像もできません！ あなたは彼を助けてここまで連れてきてくれました。あなたのおかげで私は再び生きることができました！ 私は息子のためなら何でもします。これまで彼が受けられなかった愛情を、すべて注いでやります。";
			link.l1 = "嬉しいですよ、旦那様。それにオーレのこともね。あいつはいい子で、俺が困っていた時に助けてくれたんだ。 心の優しい奴さ。オーレに命を救われた男も知っているよ。";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "旦那、ぜひ明日か、お時間のあるときにここへ来ていただきたいのです。\n息子のことでお礼を申し上げたい。今はちょっと…まあ、お分かりでしょう。";
			link.l1 = "「はい、奥様。」";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "明日またここに来てくれ。お前が私と息子のためにしてくれた善行に、きちんと報酬を与えよう。";
			link.l1 = "いいだろう。必ず会いに行くぜ！";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "ああ、ここにいたのか、旦那 "+GetFullName(pchar)+"！さあ、座ってくれ…";
			link.l1 = "ありがとう！オーレは元気か？";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "ああ、あなたがしてくれたこと、想像もできないほどよ！あなたの姿を見て、傷ついた母の心がどれだけ救われたか……恩返ししきれないわ、ずっとあなたのために祈るからね。";
			link.l1 = "照れるじゃないか、お嬢さん……";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "私はいつも、慎み深さこそが高貴な人々を高貴たらしめるものだと知っていました……あなたがしてくれたことへの贈り物を用意しました。そう、そうです！断るなんて絶対に許しませんよ！さあ、 これを受け取ってください……まずは、ドゥブロン金貨でいっぱいの箱です。次に、この魔法のアミュレットをどうぞ、スカラベと呼ばれています。\nこれは夫の持ち物でしたが、彼もきっと、自分の宝が私の息子を連れ戻してくれた高貴な船長のものになると知ったら、 喜んだことでしょう。夫は大工で、スカラベのおかげで仕事が早く進むと言っていました。\nこの指輪があなたの役に立つことを願っています。あなたが身につけるにふさわしいものです、間違いありません！ そして最後に、私の仕立て道具も受け取ってください。素晴らしい道具一式です。 きっとこれでたくさんの良いものを作れるでしょう。";
			link.l1 = "おお！これはどの船長にとっても本当に貴重な贈り物だ！ありがとう、旦那。";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received the 'Scarab' amulet");
			Log_Info("You have received a sartorial set");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "そして、私の家の扉はいつでもあなたのために開かれていることを知っておいてほしい。\nここにはいつでも食事も上等なワインも、あなたが望むものは何でもあるからな。";
			link.l1 = "ご親切なお言葉、ありがとうございます、奥様。またこの町を訪れる際にお会いできるのを楽しみにしております。";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "絶対に来いよ！";
			link.l1 = "さて、もう行かなくちゃ。さようなら、幸運を祈るぜ！";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "ああ、船長 "+GetFullName(pchar)+"！会えて本当に嬉しいよ！さあ、座ってくれ、飲み物を用意するから…";
			link.l1 = "ありがとうございます！ただご挨拶して、元気かどうか様子を見たかっただけです。 あなたもオーレも元気でよかったです。";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してるんだ、え？泥棒め！","見てくれよ！俺がちょっと物思いにふけった途端に、お前は俺の箱を調べる気になったんだな！","俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "何だと！？俺の宝箱を調べるつもりか？そうはさせねえぞ！";
			link.l1 = "「愚かな娘め！」";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
