// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もう俺に質問しようとしただろ "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港のことについて話すことがないなら、俺に質問して邪魔しないでくれ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","「まったく、これでもう三度目だな……」","悪いが、今は港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "ごきげんよう。フランソワ・ゴンティエ船長がどこにいるか教えていただきたい。重要な用件があるのです。";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "私は商人で、カラカスから来た者です。そして、こちらの港役人の同僚があなたに書簡を届けてほしいと頼まれました…";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "ああ、支払いを受け取りに来たんだ。";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "重要な用件だと？どれどれ。ふむ……フランソワ・ゴンティエがコルベット『"+pchar.questTemp.Slavetrader.ShipName+"「…私の記録によれば、ゴンティエ旦那はジャマイカへ向かっていた。」";
			link.l1 = "ありがとうございます！とても助かりました！";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "ああ、やっと来たか！お前は商人だって？またしても連中は使い走りに金を使いたくなくて、 荷の発送を最後のクソみたいな…ああ、まあ、そうだな！確かにそうだ。で、こんな短期間でどうやって艦隊を装備しろってんだよ…";
			link.l1 = "無責任そうだな……";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "そういう言い方もあるな！まあ、仕方ねえ。いずれ会うことになるさ……いや、俺の独り言だ、気にすんな。なあ、もしかしてお前、戻るつもりか？";
			link.l1 = "実はここで商品を売るつもりだったんだが、それから――そうだな、カラカスに戻るつもりだったんだ…";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "素晴らしい！では、私が返事を書いて、君に届けてもらおう。\nそうだな……十日以内に必ず届けてくれ、さもないと向こうも何もできなくなる……\nそれから、君の名前を名乗りなさい。";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "私の名前は "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "俺の名前はアンドレアス・ガルシアだ。";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "ちょっと待て……記録した。はい、どうぞ。覚えておけ、十日間だ！その間に、お前が持ってきたものをもっと詳しく読ませてもらうぞ。";
			link.l1 = "ああ、覚えているよ。じゃあな！";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "ちょっと待て……よくわからねえ……もう一度言ってくれ、お前の名前は何だった？";
			link.l1 = "俺か？…まあ…そんなに大事なことか？";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "とても重要なんだ！こう書いてある……だから…… "+n+" "+month+"…いや、違うな……12、50、69、55……だが、どこだ……ああ、あった！この手紙は船長が届けなければならん "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+"。で、名前は…… "+GetFullName(pchar)+"?";
			link.l1 = "何かの間違いがあったに違いない……";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "いや、間違いはありえない。俺が渡した手紙を返してくれ。これをはっきりさせなきゃならねえんだ！";
			link.l1 = "さあ……俺が届ける、全部うまくいくさ。";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "「嫌だ！手紙を返せ！衛兵！！！」";
			link.l1 = "「ほう、強硬手段で来るつもりか？」";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			LICENSE_AddViolation();
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "ちょっと待てよ……よし、できた。返答の手紙にお前の名前を書いておくぜ。ほら、これだ。覚えておけ、期限は十日間だ！その間に、 お前が持ってきたものをじっくり読ませてもらうぜ。";
			link.l1 = "ああ、覚えている。じゃあな！";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "「支払いか？‥‥」";
			link.l1 = "カラカスで、あなたの同僚が手紙の配達料を払ってくれると聞きました。";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "いや、まったく、あそこは完全にイカれてやがる！今度は俺があいつらの分まで払わなきゃならねえのか！";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "「それで、いくら約束されたんだ？」";
			link.l1 = "「五千ペソ。」";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "「一万ペソ。」";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "どうやら、奴らは俺の金であそこに住むことにしたらしい……。\n使者に金を使うのも嫌がって、通りすがりの商船に用事を任せるだけじゃなく、費用まで俺に押し付けやがる！\nハバナに奴らのことを訴えてやるぞ！";
			link.l1 = "旦那、お怒りはごもっともですが、私はどうすればよいのでしょうか？";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "どうやら、あいつらは俺の金であそこに住むことに決めやがったらしい……。使い走りに金を使うのも嫌がって、通りすがりの商船に用事を任せるだけじゃなく、費用まで俺に押し付けやがる！ ハバナにやつらのことを訴えてやるぞ！";
			link.l1 = "あなたの憤りは理解します、旦那。ですが、私はどうすればよいのでしょうか？";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "ああ、カラカスの新スペイン役人どもの強欲さはお前のせいじゃねえよ。だが、今はそんな大金持ってねえんだ。 資金が届くのは明日になっちまう……。\nここで待っててくれ、今から金貸しのところへ行ってくる――すぐ戻るぜ。";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "お待たせしました。こちらがあなたの\n "+makeint(pchar.questTemp.SharkGoldFleet)+" エイト金貨だ。そして今回は、奴ら自身がカラカスで答えの代金を払うことになる。俺がそう言ったと伝えてくれ。";
			link.l1 = "わかった、伝えておくよ。ありがとう、幸運を祈るぜ！";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
