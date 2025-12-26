void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "バグだ。開発者に必ず伝えてくれ。";
			link.l1 = "了解だ。";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "お待ちしていました、船長。私の提案の詳細について話しましょう。なぜこれを公の場で話したくなかったか、 お分かりいただけるはずです。";
			link.l1 = "続けてくれ、旦那。聞いているぞ。";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "俺は、～で突き止めることができた "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" の旗の下にある小さな交易船団 "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+"、交易船二隻と護衛船一隻が、まもなく近くを航行するだろう "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+"、ここは～から遠くない "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"。商人たちはたくさんの "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 船倉に隠しているんだ。この情報を利用しない手はないぜ、船長\nあんたと俺なら見張りなんざ簡単に片付けて、積み荷をいただけるってわけだ。どうだ、乗るか？";
					link.l1 = "魅力的だな。俺は賛成だぜ！";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Some"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 「俺が関係を壊すには足りねえな」 "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"「……いや、俺はこんなことやらねえ！じゃあな、旦那、止めようなんて思うなよ！」";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "俺が突き止めたのは、\n "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" の旗の下にある小さな交易船団 "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+"、交易船二隻と護衛船一隻が、出航するのは "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" へ "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+"。商人たちはたくさん持っている "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 船倉にあるんだ。この情報を利用しない手はないぜ、船長。\nあんたと俺で衛兵どもを簡単に片付けて、積荷を自分たちのものにできる。一番難しいのは、 この二つの植民地の間の外洋で奴らを見つけることだ。どうだ、乗るか？";
					link.l1 = "魅力的だな。俺は賛成だぜ！";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Some "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 「俺が関係を壊すには足りねえな」 "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"「……いや、俺はこんなことやらねえ！じゃあな、旦那、止めようなんて思うなよ！」";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "「という名の海賊について聞かされた」 "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+"。こいつは最近盗みを働いた "+RandPhraseSimple(RandPhraseSimple("English","French"),RandPhraseSimple("Spanish","Dutch"))+" そして船倉に積み込んだのは "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"。しかし、残念だが、彼の船が "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Name")+"Acc"))+" ひどく損傷したため、修理にしばらく時間がかかった。\n現在は "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" の "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"。だいたいかかると思う "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" 彼にマストや船体の穴を修理させるんだ。急げば間に合うし、俺たち全員が "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" 俺たちのものになるぜ\nこの海賊は俺一人じゃ手に負えねえ、あいつは腕の立つ船乗りで戦いも強い。でも、 二人でかかれば経験があっても勝てるはずだ。どうする、乗るか？";
					link.l1 = "魅力的だな。俺は賛成だぜ！";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "ふむ。この獲物はお前だけじゃなく、俺たち二人にも手が届かねえようだな。いや、俺はやらねえ。じゃあな、旦那、 止めようなんて思うなよ！";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "お前なら頼りになると分かってたぜ！一分たりとも無駄にしねえぞ。自分の船に行って先導してくれ、俺が後に続く。 出航の時だ！";
			link.l1 = "錨を上げる命令を出してくれ、船長！";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "「それで、なんで俺はあんたなんかと関わっちまったんだ、船長？あんたのせいで、 こんなに貴重な獲物を逃しちまったじゃねえか！次は一人で航海した方がマシだな……」";
			link.l1 = "お前のせいだ、俺のじゃねえ。じゃあな。";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			npchar.location = pchar.location;
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "お前は本当にダメな奴だな、船長！俺たちは分け前をもらえなかったじゃねえか！全部お前のせいだ！ 失敗したのはお前のせいだ、くそったれ！";
				link.l1 = "俺がか？自分を見てみろよ！お前は戦いで俺を助けなかったじゃねえか！お前と一緒にいて時間を無駄にしただけだ……俺の船から降りろ！";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "まあ、この襲撃は思ったほど上手くいかなかったな、獲物も本当にしょぼいぜ……まあいいさ、船長、この端金を分け合って、お別れとしようじゃねえか。";
				link.l1 = "もしお前が空の鳥を数えてばかりいないで俺を手伝ってくれていたら、襲撃はうまくいってたんだぜ……ほら、取り分を持っていけ― "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" そして消え失せろ！";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "よくやったな、船長！言った通りだろう――あの商人どもの貨物倉を空っぽにするなんざ、楽なもんだったぜ、ははは……戦利品は "+FindRussianQtyString(iQty)+" 分け前だ。俺の取り分は "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "正しい。 "+npchar.name+"。俺は異議ねえよ。今まさにロングボートに荷物を積み込んでるところだ。もしかしたら、 また今度一緒に襲撃に行くこともあるかもな？お前は俺にとってちょうどいい相棒みたいだぜ。";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "素晴らしいぜ、船長！言った通りだ――あの商人どもの貨物倉を空にするのは思ったより簡単だったな、はは……戦利品はでかい、予想以上だ。これは "+FindRussianQtyString(iQty)+" 分け前だ。俺の取り分は "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "「その通りだ」 "+npchar.name+"。異論はねえよ。今ちょうどロングボートに積み込み中だ。もしかしたら、また今度一緒に襲撃することもあるかもな？ お前は俺にとってちょうどいい相棒みてえだ。";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем ещё одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "可能性はあるぜ、船長。もし俺一人じゃ追えねえ儲け話がまた見つかったら、お前を探すさ。 戦でも頼りになる相棒に見えるからな。";
			link.l1 = "いいね！じゃあな、船長。幸運を祈るぜ！";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "お前なら頼りになると思ってたぜ！一刻も無駄にしちゃいけねえ。自分の船に戻って先導してくれ、俺が後に続く。 出航の時だ！";
			link.l1 = "錨を上げるよう命じてください、船長。";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "お前なら頼りになると思ってたぜ！一刻も無駄にしちゃいけねえ。自分の船に行って、俺を案内してくれ。出航の時だ！";
			link.l1 = "錨を上げるよう命じてください、船長。";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "貴様は臆病者だ、くそっ！今さっき戦場から逃げやがったな！";
			link.l1 = "「それで俺にどうしろって言うんだ？あの海賊に船を沈められて黙ってろってか？冗談じゃねえ、 死んだ馬鹿になるくらいなら生きてる臆病者の方がマシだぜ！」";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "「それで、なんで俺はあんたなんかと関わっちまったんだ、船長？臆せず斬り込みに行ける男を探すべきだったぜ！」";
			link.l1 = " さて、俺の船から降りてくれ。修理が必要なんだ。";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "お前は本当にダメな船長だぜ！俺たちは戦利品を一つも手に入れられなかったじゃねえか！全部お前のせいだ！ 失敗したのはお前のせいだ、くそっ！";
				link.l1 = "俺がか？自分を見てみろよ！お前は戦いで俺を助けなかったじゃねえか！お前と一緒にいて時間を無駄にしただけだ……俺の船から出て行け！";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "まあ、この襲撃は思ったほど成功しなかったな、戦利品も本当にしょぼいぜ……まあいいさ、船長、このわずかな分け前を分け合って、お別れといこうじゃねえか。";
				link.l1 = "もしお前が空の鳥を数えるんじゃなくて俺を手伝ってくれてたら、襲撃はうまくいってたんだぜ……ほら、お前の取り分だ― "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" そして消え失せろ！";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "よくやったぞ、船長！戦利品は "+FindRussianQtyString(iQty)+" 分け前だ。俺の取り分は "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "正しいです。 "+npchar.name+"。異論はねえよ。今まさにロングボートに荷物を積み込んでるところだ。また会うこともあるかもな……";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "素晴らしいぜ、船長！言っただろう、楽勝だったって、ははは……賞金はでかいぜ、俺の予想をはるかに超えてる。そいつは "+FindRussianQtyString(iQty)+" 分け前だ。俺の取り分は "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "「その通りだ」 "+npchar.name+"。俺は異論はねえ。今、ロングボートに積み込み中だ。もしかしたら、また一緒に略奪に行くこともあるかもな？ お前は俺にとってちょうどいい相棒に見えるぜ。";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+"、自分の船に戻れ。おしゃべりしてる暇はねえ。出航するぞ！";
			link.l1 = "ああ、ああ、もちろん、その通りだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "ふん……俺はやらねえよ。消え失せろ！自分でやるぜ！";
			link.l1 = "ほう、ほう、それじゃあ、良い旅を…";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
