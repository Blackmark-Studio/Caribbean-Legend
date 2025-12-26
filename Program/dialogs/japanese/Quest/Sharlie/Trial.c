// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "こんにちは。あなたが "+GetFullName(pchar)+"?";
			link.l1 = "おっしゃる通りです、ルクロワ様。船長 "+GetFullName(pchar)+" お仕えします。モスクワ人のファディがあなたを私に推薦してくれました…";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "ああ、そうだとも。親愛なる友人ファデイが君と君の状況について詳しく話してくれたよ。君が入口に現れた瞬間、 すぐに君だと分かった。さて、船長、君の船はどんな船なんだい？";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "ああ……今は船を持っていません、旦那……";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "「私には」 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+"、彼女の名前は "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "はっ！じゃあ、船を持ってないなら一体どんな船長なんだ？申し訳ないが、旦那、 そういうことなら君に頼める仕事はないんだ。じゃあな、ファディによろしく伝えてくれ！";
			link.l1 = "ふむ……";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "それでは全く話になりませんね。あれは船じゃなくて、ただのボートですよ、旦那。残念ですが、旦那、 あなたにはその役目は似合いません。ファディによろしく伝えてください、ではごきげんよう！";
			link.l1 = "ふむ……";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "あなたと私はもうすべて話し合いましたよ、旦那。そうではありませんか？";
			link.l1 = "はい、LeCroix様……今向かいます。";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "素晴らしい。それなら、君は俺にぴったりだ。すぐに出航する準備はできているか？";
			link.l1 = "はい、旦那、準備はできています。私は何をすればよろしいですか？";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "フランス領イスパニョーラのポルトープランスへ火薬と爆弾の小さな積み荷を届けなければならない。 司令官はしばらく前からそれを待っているから、ぐずぐずしている暇はないぞ、残りはおよそ十日間だ\n敬具 "+GetFullName(sld)+" お届けと積み込みは私が引き受けます。任務の報酬として、司令官があなたに五千エイト銀貨を支払います。";
			link.l1 = "「それで全部の仕事か？」";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "とんでもございません、旦那。弾薬を持ってきた時に、本当の仕事は司令官が説明してくれますよ。今回の貨物は、 これからあなたがやる仕事のほんの前菜にすぎません。\nでもご心配なく、うまくやれば、かなりの金が手に入りますから。";
			link.l1 = "私の注意はすべてあなたに向いております、旦那。私の船は貨物を積み込む準備ができております。";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "それじゃあ、時間を無駄にしないようにしようぜ、船長！自分の船へ向かって出航の準備をしてくれ。";
			link.l1 = "行ってくる！";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "「何かご用でしょうか、旦那？」";
			link.l1 = "ごきげんよう、船長。あなたがフロリアン・ショーク船長でいらっしゃいますね？";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "そうだ。君はポルトープランスから来た定期船じゃなかったか？";
			link.l1 = "ああ、十五門の大砲を用意したぜ。納期ギリギリで、なんとか間に合わせたんだ……";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "ふむ。旦那、あなたのユーモアのセンスは変わってますね！どういうわけか、 あなたの船から十五門の大砲が降ろされているようには見えませんが…";
				link.l1 = "ええとですね、浸水があって、積み荷の一部を海に投げ捨てざるを得なかったんです……";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "お会いできて嬉しいかい、船長？…";
				link.l1 = ""+GetFullName(pchar)+"。船長 "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "はじめまして。時間を無駄にせず、さっさとこの大砲を積み込もう。簡単な作業じゃないから、 あんたの部下にも手伝ってもらうぞ。";
			link.l1 = "何とかなるさ。おい、そこのお前、ヤードアームにブロックとタックルを設置しろ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "この馬鹿野郎！こんな簡単な仕事すらできねえなら、次の嵐で沈むのは間違いねえぞ。さっさと自分の船に戻るんだ、 船長。お前には貴婦人に花でも届ける方が向いてるだろうよ。いや、いっそヨーロッパに帰って、 新世界は本物の男たちに任せておけ。じゃあな、旦那！";
			link.l1 = "でも……";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "ふう、喉が渇く仕事だったぜ！ご苦労さん、船長！これが報酬だ、ドゥブロン金貨二百枚受け取ってくれ。";
			link.l1 = "ありがとう！";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			dialog.text = "しかし、それだけじゃありませんよ、船長。さらに金のダブルエスクード75枚を稼ぎたいと思いませんか？";
			link.l1 = "それは面白そうですが、それを得るために俺に何をさせるつもりなのかによりますよ、旦那。";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "嘘はつかないが、危険だぜ。もう知ってるかもしれねえが、 俺は貴重な積荷を積んだスペインの大型ガレオン船を待ち伏せしてるんだ。その船は修理のためにドック入りしていた。 俺の情報によれば、昨日出航するはずだったが、そうはならなかった\nそれに、ポルトベロにいる俺の手先が、ずっと待っていた情報を届けるための合流地点に現れなかった。 スペイン人に捕まったんじゃねえかと疑ってる。お前に金を払うから、 こっそりポルトベロに忍び込んで二つのことを調べてきてくれ：なぜガレオン船がまだそこにいるのか、 そして俺の手先に何があったのか。やるか？";
			link.l1 = "そのような作戦に必要な訓練は、あいにく私にはございません。私は紳士であって、間諜ではありませんから。 私自身が窮地に陥るかもしれませんし、あなたのお力にもなれないでしょう。";
			link.l1.go = "florian_deck_bye";
			link.l2 = "危険そうだが、儲かりそうだな。やってみるぜ。お前の部下の名前と、そのガレオン船の名前は何だ？";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "ほう、お偉いさん気取りか？気持ちは分かるよ。それじゃあ、船長、改めて助けてくれてありがとう、さようなら！";
			link.l1 = "ごきげんよう、Shoke様。";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "ああ、よく聞け。俺の部下の名はシルヴァン・ラフォレだが、 ポルトベロではハイメ・シリシオという名の商人として通っている。ガレオン船の名は「アルカンタラ」だ。 忠告しておくが、夜に街門を抜けてジャングルを通るのがいい。最近のポルトベロの衛兵はやたらと疑り深いし、 シルヴァンが行方不明になったことで、彼が無事だとは思えねえ。スペインの巡回隊に見つかる前に、 俺がここを離れなきゃならねえまで二日しかねえ。幸運を祈るぜ、旦那！";
			link.l1 = "また会いましょう、Shoke様……";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "全部話し合ったな、船長、そうだろう？";
			link.l1 = "はい。今向かっている。";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "調子はどうだ、船長？何か分かったことはあるか？";
			link.l1 = "状況は悪い方向に進んでいます、Shoke様。私はあまりスパイ向きではなく、すぐに正体がばれてしまいました。衛兵たちと戦った末、 街から逃げ出さざるを得ませんでした。唯一わかったのは、あなたの部下であるシルヴァン・ラフォレが逮捕され、 牢に入れられているということだけです。";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "くそっ！まずいな……ガレオン船について何か分かったか？";
			link.l1 = "いいや、していない。";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "くそっ。本当にその件について情報が必要なんだ。でも、この獲物はデカすぎて手放せねえ！とにかく、 もう一人偵察を送り込んでみるさ…船長、しばらく俺のそばを離れないでくれ。お前の助けが必要になるかもしれねえ。 アラカンタラについて情報を探ってる間、もう一日待ってくれるか？";
			link.l1 = "もちろん、待つよ！あの失敗を取り返したいんだ。";
			link.l1.go = "florian_9";
			link.l2 = "そうは思わないな。どうやら俺はこういう遊びが下手みたいだ。家に帰るよ。";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "まあ、それはあなたの選択だ。幸運を祈るぜ、船長。";
			link.l1 = "さらばだ、Shoke様。";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "調子はどうだ、船長？何か分かったことはあるか？";
			link.l1 = "状況は芳しくありません、Shoke様。私はあまりスパイ向きではなく、すぐに正体がばれてしまいました。唯一わかったのは、 あなたの部下であるシルヴァン・ラフォレが逮捕され、どこかに拘束されているということだけです。";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "それでは自分の船に戻ってください、船長。明日の同じ頃か、少し遅れてでも、私のところに来てもらう必要があります。 その時までには何かわかるかもしれません。上陸せずに、船で私を待っていてください！";
			link.l1 = "わかった。やっておく。";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "「それから船長、この財布を受け取ってくれ。君の努力も、結局はまったく無駄じゃなかったな。少なくとも、 哀れなシルヴァンに何が起きたかは分かったんだから……」";
			link.l1 = "...";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "船長、今のところ何の知らせもありません。まだ待っているところです…";
			link.l1 = "「よし……」";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "調子はどうだ、船長？何か分かったことはあるか？";
			link.l1 = "終わったぞ。お前の部下、シルヴァン・ラフォレは逮捕されて牢に入れられている。あいつの人生はもう終わりだ。";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "くそっ！ひでえな……ガレオン船について何か分かったのか？";
			link.l1 = "はい。彼女はしばらく前から出航の準備を進めていたが、ポルトベロの総督が桟橋に留め置くつもりらしい。\n今は「プエブラ」というバーク船がカルタヘナから「アルカンタラ」向けの火薬を積んで到着するのを待っているそうだ。 ガレオン船の水夫によれば、火薬が十分に揃っておらず、総督は海賊を恐れているらしい。";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "「これは面白い！」";
			link.l1 = "しかし、プエブラが三日以内に到着しなければ、アラカンタラ号は待つのをやめて出航するだろう。";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "素晴らしい働きだ、船長 "+GetFullName(pchar)+"！とても嬉しいぞ！さあ、報酬を受け取れ。本当にお前はよくやった！";
			link.l1 = "ありがとうございます！他に何か任務はありますか？";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 75);
			dialog.text = "「私の心を読んでいるのですね」 "+GetFullName(pchar)+"「そうだ、くそっ！アラカンタラは火薬が少ないから、あいつを外海に誘い出して長期戦に持ち込めば、 向こうの火薬が先に尽きるってわけだ、ははは！\n補給用のバーケンティン、プエブラが絶対にポルトベロに到着しないようにしろ。俺は岸に近づけねえ。 巡回が俺のフリゲートをすぐ見つけて、アラカンタラを捕まえる前に追い払われちまうからな\nプエブラはお前が自分で片付けろ。見つけて始末しろ。沈めても拿捕しても構わねえ。とにかくここに来させるな！\nうまくやったら、グアドループに行ってジェラール・ルクロワに会え。あいつのことはもう知ってるだろ？ お前の働きに見合う報酬を払ってくれるさ。」";
			link.l1 = "取引成立だ！俺はこれからプエブラを遮断しに向かうぜ！";
			link.l1.go = "florian_19";
			link.l2 = "少々お待ちください、ショケ船長。実は私、まだ……そうですね、海戦にはあまり慣れていないのです。それに、あなたはフリゲート艦の船長でいらっしゃる。 明らかに何度も海戦を経験されているのでしょう。もしご迷惑でなければ、その……どう申し上げればよいか……";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "来てくれて嬉しいぜ、船長。ちょうど今、俺の間者から情報が入ったんだ。お前に頼みたい重要な任務がある。";
			link.l1 = "聞く耳は持っているよ。";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "アラカンタラ号は出航の準備ができているが、 ガレオン船の船長はカルタヘナから弾薬を満載して到着するバーケンティン船「プエブラ」を待っているようだ。 どうやらアラカンタラ号には火薬が十分にないらしく、スペイン人たちはまだ出航できない。しかし、 船長の我慢にも限界があり、もしプエブラが三日以内に来なければ、 ガレオン船は彼女を待たずにポルトベロを出港するだろう。\nアラカンタラ号は火薬が不足している。あの船を外海に誘い出し、長期戦に持ち込めば、 向こうの火薬が先に尽きるはずだ。お前の任務はプエブラを捕捉し、撃沈するか拿捕することだ。沈めても、 戦利品として奪っても構わん。とにかく補給のバーケンティン船をここに到着させるな！\n成功したら、グアドループへ行き、ジェラール・ルクロワに会え。彼のことはすでに知っているだろう？ 彼がお前にふさわしい報酬を払ってくれるはずだ。";
			link.l1 = "取引成立だ！俺はこれからプエブラを断ちに行くぜ！";
			link.l1.go = "florian_19";
			link.l2 = "少々お待ちください、ショケ船長。実は私、まだ……まあ、正直に言えば、海戦にはあまり慣れておりません。それに、あなたはフリゲート艦の船長でいらっしゃるし、 当然ながら何度も海戦を経験されているのでしょう。もしご迷惑でなければ、その……どう申し上げればよいか……";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "私に海戦戦術の講義をしてほしいと？喜んでお受けしますよ、船長！\n特に今回は私自身の利益にもなりますからね――あなたが『プエブラ』を無事に拿捕できると確信したいのです。";
			link.l1 = "いや、そんなつもりじゃなかった。まあいい、忘れてくれ。バルク船くらい、俺が拿捕するのに苦労はしないさ。";
			link.l1.go = "florian_19";
			link.l2 = "そう、それがまさに私の言いたかったことです。新しい知識が私に害を及ぼすことはないでしょう。";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "だから、まず覚えておくべきことは、戦いの半分は始まる前にすでに勝敗が決まっているということだ。\nどれだけ自分と船が準備できているかで、結果は大きく変わるんだぜ。";
			link.l1 = "...";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "まずは、自分の船をきちんと修理しておけ。船体に穴が空いていれば、敵に沈められるのは簡単なことだ。 帆がボロ布のように垂れ下がっているなら、機動力も大きく制限されるぞ。戦力差が不利なら敵は簡単に逃げられるし、 逆に追いつかれて不利な戦いを強いられる――あるいは即座に乗り込まれることだってある。さらに、帆が破れていれば「ウェザーゲージ」――つまり敵より風上に立つことも難しくなる。風上を取るのは、まさにお前が目指すべき位置だ。";
			link.l1 = "風上を取る、了解だ。他に何かあるか？";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "十分な人数を確保しておけ。どんなに強力な42ポンド砲搭載の船でも、砲手が一人で三門の大砲を装填し、帆を扱う者すらいなければ、まるで役に立たねえ。\n正直、そんな船なら俺なら即座に乗り込んで奪ってやるぜ。";
			link.l1 = "「十分な人数だな、了解。」";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "それから、大砲にも気をつけろよ。時間が経つと摩耗して爆発することがあるんだ。砲身の状態は悪化していくし、 戦闘中に大砲が爆発し始めたら、お前にとって最悪の事態になりかねない。俺は全く運がなかったよ――乗っていた大砲のロットには鋳造不良がいくつもあったんだ。お前がタイミングよく予備を持ってきてくれなかったら、 作戦はあきらめていただろうな。ミリタント号は火力でアルカンタラ号に大きく劣るからな。 道具は早めに交換しないといけないぜ。";
			link.l1 = "今になって、なぜそれがそんなに重要だったのか分かった！";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "大砲だけでなく、弾薬の量にも注意を払え。アルカンタラはこの点で俺のものになる。 もしあいつの火薬の備蓄が少なければ、長期戦はできず、すぐに接近戦に持ち込まざるを得なくなる。 そこを俺は利用する。俺のフリゲートは速い、重ガレオンは逃げ切れねえ。だが、俺も無理に接近する必要はない。 遠距離で砲撃戦を強要し、アルカンタラの火薬が尽きたところで距離を詰め、ぶどう弾で掃射してから乗り込んでやる。";
			link.l1 = "絶体絶命の状況だな……";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "その通りだ。火薬と弾薬には十分注意しろ。もし実弾が尽きれば、敵船を沈めることはまずできねえ。 ブドウ弾がなくなれば、数で劣るときに白兵戦を仕掛けるのは無理だ。チェーンショットやニップル弾がなければ、 敵に追いつくことも、速い敵から逃げることもできねえ。どの弾薬も大事なんだぜ。";
			link.l1 = "勉強になりました、ありがとうございます。";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "そして最後に、自分の船と敵船の種類や大きさに応じて、適切な戦術を使うことだ。 海では火力と速度のバランスが重要だぜ。 大型で鈍重な船でブリッグやコルベットを追いかけて拿捕しようとしても意味がねえ――まずはチェーンショットで相手を弱らせないと追いつけやしない。そんな時は、 遠距離からぶっ壊して残骸を漁る方が賢明だ。どうしてもそういう船に乗り込む必要があるなら、 速くて小回りの利く船を使うのが望ましいぜ。";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "同時に、ブリッグで戦列艦と正面からやり合うのはやめておけ。あんな化け物の一斉射撃を食らえば、 小型船の船体なんざ木っ端微塵だ。お前の持ち味である速力と機動力を活かして、まずは敵のマストや索具を叩き折れ。 それから接近して、もし乗り込む必要があるなら、甲板にブドウ弾を浴びせてやれ。もし沈めたいなら……簡単じゃねえが、不可能じゃない。乗り込んで火薬庫に火をつける手もあるが、逃げることは決して恥じゃねえ。 優れた船長は、無駄な英雄気取りよりも、船と乗組員を確実な死から救うもんだ。覚えておけ、慎重さと分別こそが、 しばしば勇気よりも大切なんだぜ。";
			link.l1 = "本当にありがとうございます、ショケ様！";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "お役に立てて嬉しいです、船長。\nこの知識が今後あなたの助けになることを願っています。";
			link.l1 = "きっと役に立つはずだ。俺たちは「プエブラ」を迎え撃ちに行くぞ！";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "お前、変わった訛りだな、旦那。それとも「ムッシュ」と呼ぶべきか？ハイメ・シリシオに会いたいのか？ 同じ牢に入れてやってもいいぜ。連れて行け、野郎ども！\n";
			link.l1 = "俺の訛りが気に入らねえなら、フランス流の剣術をお見舞いしてやろうか！";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
