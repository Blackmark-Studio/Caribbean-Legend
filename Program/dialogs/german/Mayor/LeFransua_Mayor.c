// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was willst du? Frag los.","Ich höre dir zu, was ist die Frage?"),"Das ist das zweite Mal, dass du versuchst zu fragen...","Das ist das dritte Mal, dass du versuchst zu fragen...","Wann wird das endlich aufhören?! Ich bin ein beschäftigter Mann, arbeite an Kolonialangelegenheiten und du belästigst mich immer noch!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Ich möchte über Ihren Gefangenen sprechen.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hallo "+NPChar.name+", ich bin hier wegen Ihres Gefangenen.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Ich möchte über Ihren Gefangenen sprechen.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ich habe gehört, dass du dich mit einem Geschäft im Zusammenhang mit Gefangenen beschäftigst...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "Ha-ha. Glaubst du, ich habe hier nur einen Gefangenen? Nenne seinen Namen.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ist er hier?";
			link.l1.go = "CapComission2";
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Er war es. Ich habe ihn an diesen Plantagenbesitzer aus Barbados verkauft - Oberst Bishop, als er vor einer Woche hier war.";
				link.l1 = "Verdammt...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Ach, endlich. Ich dachte schon, ihn an diesen Plantagenbesitzer aus Barbados zu verkaufen, der wird in einer Woche oder zwei hier sein... Hast du ein Lösegeld?"+GetSexPhrase("","")+"?";
				link.l1 = "Schau, "+NPChar.name+" , es gibt ein kleines Problem ... Eigentlich habe ich nicht so viel Geld. Aber ich bin bereit zu arbeiten.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn bekommen?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Du warst zu langsam... Und warum kümmert er dich? Ich habe nur mit seinen Verwandten verhandelt.";
			link.l1 = "Sie haben mich gebeten, hierher zu kommen.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Nun, du bist spät dran. Ich kann nichts machen.";
			link.l1 = "Hör zu, für wie viel hast du ihn verkauft, wenn es kein Geheimnis ist?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, das ist es nicht. Aber ich werde es dir nicht sagen... Du wirst lachen, wenn ich es tue. Ha-ha-ha-ha! Lebewohl.";
			link.l1 = "Bis dann.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Nun, nun.. Ich habe ein Geschäft... Weiß nicht einmal, wie ich anfangen soll. Ich muss einen Piraten versenken, der zu weit gegangen ist.";
				link.l1 = "Kann er nicht einfach im Dschungel getötet werden?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Nun, "+pchar.name+", weißt du, so funktioniert es nicht. Komm zurück mit dem Geld und du bekommst deine Schwächling, ha-ha.";
				link.l1 = "Gut, dann leb wohl.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Das ist nicht, wie Geschäfte laufen, weißt du... Ich brauche seinen Tod nicht, ich muss einigen Leuten beibringen, meinen Teil der Beute nicht anzurühren. Aber wenn er den Haien zum Fraß voran geht, werde ich nicht verärgert sein.";
			link.l1 = "Warum schickst du nicht deine eigenen Leute hinter ihm her?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Hm.. Nun "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" hat einige Piraten davon überzeugt, dass ihr Anteil an der Beute in unserem Versteck nicht weit von hier aufbewahrt wird "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Ihre zwei Schiffe '"+pchar.GenQuest.CaptainComission.ShipName1+"' und '"+pchar.GenQuest.CaptainComission.ShipName2+"' hat vor kurzem die Anker gelichtet und ist nach "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+". Jetzt siehst du, warum ich meinen Männern diesen Job nicht anvertrauen kann?";
			link.l1 = "Ich verstehe. Wie viel Zeit habe ich?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 bis 15 Tage, nicht mehr. Es ist mir wichtig, dass sie nicht an den Vorrat kommen, es wäre Unsinn, sie mit wertvoller Ladung zu versenken. In diesem Fall wäre es besser, wenn sie es hierher bringen würden...";
			link.l1 = "Gut, ich bin dabei. Ich werde versuchen, sie zu fangen.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "Mach dir keine Sorgen. Meine Männer werden ihn zu deinem Schiff bringen. Und warum kümmert er dich?";
			link.l1 = "Ich nicht. Seine Verwandten baten mich, ihn zu liefern.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, das ist gut. Ich war fast traurig, einen so niedrigen Preis für deinen Mann zu geben. Ha-ha-ha-ha. Lebewohl.";
			link.l1 = "Bis dann.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "Nun, "+GetFullName(pchar)+", hast du meinen Kumpel versenkt? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nein. Ich habe es nicht geschafft, sie zu fangen. Und ich habe sie bei der Rückkehr nicht getroffen.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "Ich habe. Ich habe sie geschickt, um die Haie zu füttern.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Verdammt! Egal, es spielt jetzt keine Rolle mehr! Was wird dein nächster Vorschlag sein?";
			link.l1 = "Vielleicht hast du eine einfachere Aufgabe für mich?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Hör zu, "+NPChar.name+", senke den Preis für den Gefangenen...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nein.";
			link.l1 = "Dann auf Wiedersehen...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "Den Preis senken?! Ich habe gerade meinen Vorrat wegen deiner Inkompetenz verloren! Jetzt kann ich den Preis erhöhen! Du kannst ihn für 200.000 Pesos haben, wenn du willst, oder du kannst zum Teufel hier raus!";
			link.l1 = "Es ist zu teuer... Auf Wiedersehen...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Verdammt, gut, nimm deine Münze.";
				link.l2.go = "CapComission4_5";
			}	
		break;
				
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Du kannst diesen Schwächling nehmen...";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "Ho-ho! Gut gemacht! Nimm deinen Schwächling und viel Glück.";
			link.l1 = "Danke. Lebewohl.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "Hast du das Geld gebracht, Charles? Ich habe nicht gescherzt, als ich sagte, dass ich diesen Mann an die Plantage verkaufen würde";			
			link.l1 = "Hör zu, "+NPChar.name+", es gibt ein Problem... Ich habe nicht so viel Geld. Aber ich bin bereit zu arbeiten.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn abholen?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "Und warum kümmert es dich, was ich tue? Weißt du, du solltest besser gehen...";
			link.l1 = "Tshh, beruhige dich. Ich habe ein Geschäftsangebot für dich. Es geht um deinen Gefangenen.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ach, gut. Wen möchtest du auslösen?";
			link.l1 = "Warte. Ich bin nicht hier, um auszukaufen, ich biete dir an, einen Gefangenen zu kaufen. Nun, und du wirst die Gelegenheit haben, ein Lösegeld für ihn zu bekommen.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Und warum brauchst du meine Vermittlung? Willst du das Geld nicht direkt für dich selbst bekommen?";
			link.l1 = "Es ist ziemlich riskant für mich. Ich könnte Probleme mit den Behörden bekommen.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... gut dann. Lasst uns nachsehen. Wer ist dein Gefangener?";
			link.l1 = "Das ist "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Ich verstehe. Es wäre ein guter Handel, wenn du nicht lügst. Ich nehme an, ich kann dich für diesen Mann bezahlen, "+iTemp+" Pesos, oder gebe dir stattdessen einige interessante Informationen. Es ist deine Wahl.";
			link.l1 = "Ich nehme lieber das Geld. Ich habe genug von diesem Geschäft...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Erzähl mir mehr. Ich bin sicher, dass du mir etwas Interessantes liefern wirst.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Geld also. Nimm sie. Jetzt ist es nicht mehr dein Problem. Bringe das Verkaufsobjekt hierher.";
			link.l1 = "Er muss bereits in der Nähe des Stadttors sein. Danke! Du hast mir wirklich geholfen.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Du bist willkommen, bring mir mehr... Bis dann!";
			link.l1 = "Viel Glück...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Es ist gut, Geschäfte mit einem klugen Mann zu machen. Jetzt hör zu: in ein paar Tagen zu "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" Eine spanische Expedition wird aus Main kommen, beladen mit wertvollen Gütern. Sie werden auf ein Schiff warten, das die Fracht nehmen soll. Wenn du in einer Woche dort bist, hast du die Chance, die Fracht für dich zu nehmen.\nWenn ich du wäre, würde ich mich bereits zu meinem Schiff bewegen. Und bring den Gefangenen hierher.";
					link.l1 = "Danke! Die Waren werden eine schöne Entschädigung für meine Mühen sein. Und mein Passagier muss bereits in der Nähe der Stadttore sein. Er wird zu dir gebracht.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Es ist gut, Geschäfte mit einem klugen Mann zu machen. Jetzt hör zu: in etwa einer Woche kommt eine spanische Brigantine '"+pchar.GenQuest.Marginpassenger.ShipName1+"' beladen mit wertvollen Gütern wird segeln von "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" zu "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Wenn du dich beeilst, wirst du es leicht erwischen.\nDu bist immer noch hier? Wenn ich du wäre, wäre ich bereits auf dem Weg zu meinem Schiff. Und bringe den Gefangenen hierher.";
					link.l1 = "Danke! Die Waren werden eine schöne Entschädigung für meine Mühen sein. Und mein Passagier muss in der Nähe des Stadttors sein. Er wird zu Ihnen gebracht.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
