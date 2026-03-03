void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "これはバグだ。開発者に知らせてくれ。";
			link.l1 = "やるぜ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "どうも、色白の者よ。お前が大きなカヌーの船長だと見たぞ。俺はカナウリだ。カイマン――偉大なるアラワク族の酋長だ。お前と話がしたい。";
			link.l1 = "聞いてるぜ、親分。どんな悩みで俺のところに来たんだ？";
			link.l1.go = "RedChieftain_0";
			link.l2 = "俺に何の用だ、この汚え赤い肌の猿め！自分のジャングルに帰って、俺に頼みごとなんかするんじゃねえ。";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "グーウ！白い船長は礼儀を教わらなかったのか？俺は取引を持ちかけたんだぜ。お前は山ほどワンパムを稼げたのによ、 もう行くぜ。さらばだ、色白野郎。";
			link.l1 = "さっさと失せろ……";
			link.l1.go = "RedChieftain_exit_1";
		break;
		
		case "RedChieftain_exit_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.RedChieftain");
			chrDisableReloadToLocation = false;
			ChangeIndianRelation(-3.0);
		break;
		
		case "RedChieftain_0":
			dialog.text = "白い兄弟よ、フクロウのように賢く、ヘビのように狡猾だ。\nインディアンに災いが近づいている。白人の大きな大きなカヌーが俺の村にやって来た。\n奴らは多くのカイマン――俺たちの仲間を捕まえて、自分たちのカヌーに乗せ、母なる大海へ連れて行ったんだ……";
			link.l1 = "待てよ……お前の仲間たちは、船に乗った白人どもに奴隷にされたって言うのか？";
			if (sti(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "お前の言うことは本当だな、白き兄弟よ。あの白い顔の連中が、お前の味方じゃないことは知っている。 スペイン族のあの残酷な白人どもめ。奴らは俺の仲間をさらっていく。だが、俺が奴らを見つけ出す。 スペイン人はインディアンに夜明けから日暮れまで働かせ、水の母の奥深くまで潜らせて、神々 の涙で満ちた貝殻を探させるのだ。";
			link.l1 = "真珠採りか……あれは過酷な仕事だぜ。";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "お前の言うことは本当だな、白き兄弟よ。あいつらが、お前の友じゃないことは知っている。 あいつらはイギリスの部族だ。俺の民を連れていく。だが、俺が見つけ出す。 イギリス人はインディアンたちを夜明けから日暮れまで働かせ、水の母の底まで潜らせて、神々 の涙で満ちた貝殻を探させるんだ。";
			link.l1 = "真珠採りか……これはきつい仕事だな。";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "インディアンたちは奴隷にされて病に倒れ、死んでいく。白人たちはインディアンに情けをかけない。 鞭とピストルこそが、白人がインディアンに対して使う法なのだ。わしは年老いた。もはや戦う仲間もおらん。 カイマンのアラワク族は平和を愛する民で、平和のパイプを発明したのじゃ。頼む、白い兄弟よ、 悪しき白人どもに鞭とピストルを向け、アラワク族を救ってくれ。";
			link.l1 = "俺に戦争を宣言しろってのか？分かってくれよ、親分、俺の手持ちには限りがあるんだ。";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "戦いには行かない。俺は自由なインディアンだ。俺たちの民だ。カヌーにある神々の涙は全部あんたにやる。 悪い白人を殺して、インディアンを助ければ、神々の涙が手に入る。それを売ればたくさんのワンパムになる。 山ほどのワンパムだ。";
			link.l1 = "ああ、今わかったぜ。いや、カナウリ、俺には手伝えねえ。今は無理だ――俺の船は修理が必要だし、補給ももう残っちゃいねえんだ……";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "その場合は、喜んでお引き受けします。詳しい話をしましょう。仲間はどこにいるんだ？もう見つけたって言ってたよな…";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "グーウ！俺は待てるぜ、白い兄弟よ……この港にはもう一月いるつもりだ。俺の民を守ってくれる者を探してな。準備ができたら、ここで俺を探せ。";
			link.l1 = "...";
			link.l1.go = "RedChieftain_wait_1";
		break;
		
		case "RedChieftain_wait_1":
			DialogExit();
			//LAi_ActorGoToLocator(npchar, "quest", "quest1", "RedChieftainStay", -1);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetFunctionTimerCondition("RedChieftainDelete", 0, 0, 30, false);
			
			sld = CharacterFromID("RedChieftain");
            //LAi_SetStayType(sld);
			sld.dialog.currentnode = "RedChieftain_wait_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity, false);
		break;
		
		case "RedChieftain_wait_2":
			dialog.text = "戻ってきたのか、白い兄弟よ？悪党どもを懲らしめて、インディアンを救うのを手伝ってくれるか？";
			link.l1 = "これ以上の準備はねえさ。";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "まだ準備が必要だ。";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "俺はここにいるぜ、白い兄弟よ。";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "お前が承知してくれて本当に嬉しいぜ、白い兄弟よ！";
			link.l1 = "詳しい話をしようぜ、カナウリ。お前の仲間はどこにいるんだ？もう見つけたって言ってたじゃねえか…";
			link.l1.go = "RedChieftain_5";
			pchar.quest.RedChieftainDelete.over = "yes"; //снять таймер
		break;
		
		case "RedChieftain_5":
			if (CheckAttribute(pchar, "questTemp.RedChieftain.Spa"))
			{
				AddMapQuestMarkShore("Shore19", true);
				pchar.questTemp.RedChieftain.Island = "Cumana";
				pchar.questTemp.RedChieftain.Shore = "Shore19";
				pchar.questTemp.RedChieftain.Add1 = "Spanish";
				pchar.questTemp.RedChieftain.Add2 = "Carupano Cove, not far from Cumana";
				dialog.text = "あいつらはカラパノ入り江に野営してる。スペイン人の野営地クマナの近くだ。毎日ボートで海に出て、深く、深く……水に潜ってるんだ。\n";
				link.l1 = "なるほど。それで、スペイン人が奴らが潜っている間見張っているのか？";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "やつらはケープ・ペルラスのイギリス人の野営地ブルーウェルドの近くに野営している。\n毎日ボートで海に出て、深く、もっと深く潜っていくんだ……";
				link.l1 = "なるほど。それで、もちろんイングランド人が奴らを見張ってるんだろう？";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "ああ、火縄銃と大きな刃物を持った白人どもが二艘の大きなカヌーで来ている。\n岸の野営地も見張りがいて——インディアンは逃げられねえ。";
			link.l1 = "どんな船だった？説明できるか？どれくらい大きいんだ？帆はどんな感じだった？";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "このカヌーは大きいが、カナウリはもっと大きいのを見たことがある。\n前の帆はとても、とても傾いていて、こうやって三つの面を作っている。（彼は地面に三つのラテン帆と台形の帆を描く） \n上は狭くて、下は広いんだ。";
			link.l1 = "音も見た目もスクーナーっぽいな……";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "カナウリにはその言葉は分からない。顔の白い者は、もし他のカヌーを見かけたら、十分に注意しなきゃならねえ――インディアンを岸に降ろして、もう一方のカヌーが去るまで待つんだぜ。";
			link.l1 = "用心深い野郎どもめ……どうやって近づけばいいんだ？";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "もし白い顔の兄弟が小舟を使えば、岸辺の近くまでこっそり近づける。俺が道を教える。\nだが、小舟は一つだけ持ってこい。そうしないと白い顔の犬どもに見つかって、 インディアンは舟から追い出されてジャングルへ逃げることになるぞ…";
			link.l1 = "了解だ。この作戦にはラガーかスループが必要だな。\nよし、スループでスクーナー二隻とやり合うのかよ……くそっ……楽勝だと思ってたのによ！";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "行くかい、白い兄弟？月が一つも経たねえうちにやらなきゃならねえぞ。";
			link.l1 = "ああ。俺の船に乗れ、親分。時間を無駄にするな！";
			link.l1.go = "RedChieftain_11";
		break;
		
		case "RedChieftain_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.Red_Chieftain_2.win_condition.l1 = "location";
			pchar.quest.Red_Chieftain_2.win_condition.l1.location = pchar.questTemp.RedChieftain.Island;
			pchar.quest.Red_Chieftain_2.function = "RedChieftain_CreateShooner";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("RedChieftainOver", 0, 0, 30, false);
			AddQuestRecord("RedChieftain", "1");
			AddQuestUserData("RedChieftain", "sText1", pchar.questTemp.RedChieftain.Add1);
			AddQuestUserData("RedChieftain", "sText2", pchar.questTemp.RedChieftain.Add2);
		break;
		
		case "RedChieftain_pearl":
			dialog.text = "ありがとう、白い兄弟よ！お前のおかげでカイマンのアラワク族は救われた！俺たちは大きな借りができたぜ。 道には白人どももいねえし、インディアンたちはジャングルを自由に駆け回れる。船に残っていた神々 の涙をすべてお前にやる。";
			link.l1 = "さて、どんなものを持ってきたか見せてもらおうか……";
			link.l1.go = "RedChieftain_pearl_1";
		break;
		
		case "RedChieftain_pearl_1":
			DialogExit();
			pchar.questTemp.RedChieftain.Ind = 1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_pearl_give":
			int iSmallPearl = rand(200)+rand(250)+rand(200)+250;
			int iBigPearl = rand(100)+rand(100)+rand(50)+150;
			TakeNItems(pchar, "jewelry52", iBigPearl);
			TakeNItems(pchar, "jewelry53", iSmallPearl);
			PlaySound("interface\important_item.wav");
			Log_SetStringToLog("The Chief has given you "+iSmallPearl+" small and "+iBigPearl+" big pearls.");
			dialog.text = LinkRandPhrase("神々の涙があんたのものになって嬉しいぜ、アラワク族の兄弟よ！","インディアン、ありがとう、勇敢な白人よ！","「俺たちの獲物を持ってけ、白い兄弟！」");
			link.l1 = LinkRandPhrase("助けになれて嬉しいぜ！","「ありがとう、赤い肌の兄弟！」","「すごい！」");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = sti(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(sti(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "カナウリはまた礼を言うぞ、色白の兄弟よ！お前はインディアンたちとカヌーを全部救ってくれた！カナウリにとっては、 すべてのカヌーを守ることがとても大事だ。なぜなら、 お前は悪い色白どもに奴隷にされたカナウリの孫も救ってくれたからだ。孫は子供の頃、水泳が大好きでな、 カナウリは彼が溺れないようにこの呪われたお守りを渡した。だが今、孫はもう泳ぎたくないと言って、 このお守りをカナウリに返してくれた。だからカナウリはこれをお前に渡す、色白の兄弟よ。神々の涙とこの贈り物が、 アラワクの命にふさわしい報酬となることを願う。そして今、別れの時だ――我々は故郷の村に帰る時が来た。";
				link.l1 = "幸運を祈るぜ、Cunauri！孫が生き延びて本当に良かった！もう二度とこんな災いがお前に降りかからねえよう祈ってるぜ！";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "カナウリはまた礼を言うぞ、色白の兄弟よ！神々の涙がインディアンたちの命への十分な報いとなることを願っている。 ではさらばだ、俺たちは故郷の村へ帰るぞ。\n";
				link.l1 = "幸運を祈るぜ、クナウリ！二度と奴隷になんかなるんじゃねえぞ！";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(makeint(pchar.questTemp.SanBoxTarget) == 2 ||  makeint(pchar.questTemp.SanBoxTarget) == 5)
					//{
						pchar.questTemp.SanBoxTarget.RedChieftain = true;
						ChangeCharacterComplexReputation(pchar, "fame", 25);
					//}
				//}
			}
		break;
		
		case "RedChieftain_final_1Obereg":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n1 = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n1; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			TakeNItems(pchar, "talisman10", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received Seeker's obereg");
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "9");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		// <-- legendary edition
		
		case "RedChieftain_final_1":
			DialogExit();
			RemovePassenger(Pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			int n = pchar.questTemp.RedChieftain.Tartane;
			for (i=1; i <=n; i++)
			{
				sld = characterFromId("RC_Indian_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			locations[FindLocation(pchar.questTemp.RedChieftain.Shore)].DisableEncounters = false; //энкаутеры открыть
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddQuestRecord("RedChieftain", "8");
			CloseQuestHeader("RedChieftain");
			DeleteAttribute(pchar, "questTemp.RedChieftain");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
