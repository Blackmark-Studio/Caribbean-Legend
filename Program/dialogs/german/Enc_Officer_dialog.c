// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, Kapitän, die Hälfte der Garnison ist momentan hinter dir her. Sicherlich ist es nicht die beste Zeit, in deiner Crew angestellt zu werden!","Und uns durchkämpfen bis zum Schiff? Nein, Kapitän, ein anderes Mal...");
				link.l1 = RandPhraseSimple("Wie du wünschst...","Eigentlich wollte ich dich nicht einstellen."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Brauchen Sie einen Offizier, Kapitän?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Ein Offizier? Und was kannst du gut?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Nein, ich habe das volle Set.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Kapitän, was machst du da? Steck deine Waffe weg, bevor du viel Ärger machst!";
			link.l1 = LinkRandPhrase("Gut.","Gut.","Mach dir keine Sorgen, ich räume es weg...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Heute setzen wir endlich Segel!";
				link.l2 = "Ja... Ich bin froh.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Ich beende nur meinen Drink, Kapitän, und dann gehe ich zum Schiff. Mach dir keine Sorgen - ich werde rechtzeitig da sein.";
				Link.l1 = "Also gut. Wenn du zu spät kommst, lasse ich dich das Deck schrubben!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Was wünscht ihr, Kapitän?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Ich muss Ihnen einige Befehle geben.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", Ich gehe in eine alte indische Stadt namens Tayasal. Es wird eine gefährliche und ungewöhnliche Reise sein - durch ein Teleportationsidol. Begleitest du mich?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", Ich habe eine ernsthafte Bitte an dich - ein echter Deal, selbstmörderisch aber verdammt profitabel. Ich brauche einen treuen Mann auf einer Quest in eine alte indische Stadt. Bist du bei mir?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, du hast dich einmal darüber beschwert, dass Söldner unterbezahlt sind.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Jetzt höre meinen Befehl!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Gib mir einen umfassenden Schiffsbericht, "+GetStrSmallRegister(XI_ConvertString("Schatzmeister"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Ich möchte, dass Sie Waren kaufen, während wir in der Kolonie sind.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Du weißt, wir müssen keine Waren mehr in Kolonien kaufen.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Offizier, Ihre Dienste werden nicht mehr benötigt.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "Ich mache dich zum Stellvertreter dieser Stadt!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Nichts. Bei Leichtigkeit!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "Verdammt, Kapitän! Ich dachte, du würdest mich bei der ersten Gelegenheit loswerden, aber du hast mich wie immer überrascht. Natürlich bin ich bei dir, und danke, dass du diesem Idioten das wahre Leben eines Seewolfs ermöglicht hast!";
				Link.l1 = "Gut gemacht, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "Hä? Habe ich das wirklich gesagt?";
				Link.l1 = "Du hast es getan. Ich habe dir damals genau zugehört, und ich bin bereit, das Unrecht zu korrigieren.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Entschuldigung, Kapitän, aber das ist nicht das, für was ich mich eingeschrieben habe. Denken Sie nicht, dass ich ein Feigling bin, aber ich bin nicht bereit, dem sicheren Tod ins Gesicht zu sehen. Ich habe das Leben noch nicht satt - noch nicht. Sie können mich feuern, wenn Sie möchten.","Kapitän, ich bitte um Verzeihung, aber - nein. Meere, Entern, feindliche Städte - das ist völlig in Ordnung, aber ich will mich nicht mit dieser Indianischen Hexerei einmischen. Wenn Sie mit meiner Antwort unzufrieden sind, können Sie unseren Vertrag kündigen.","Sie wollen das Unmögliche, Kapitän, und das wissen Sie. Niemand wird lebend zurückkommen, einschließlich Ihnen, also verzichte ich. Wenn Sie meine Ablehnung als Vertragsverletzung betrachten, können Sie ihn kündigen.");
			link.l1 = LinkRandPhrase("Ich mache Ihnen keinen Vorwurf, Offizier. Ich verstehe das vollkommen.","Schade, aber ich kann dich verstehen. Deshalb habe ich dir das im Voraus gesagt.","Ich habe auf dich gezählt... Aber ich kann deine Position verstehen, Offizier.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Heh! Wirst du dann meinen Lohn erhöhen?";
			Link.l1 = "Auf keinen Fall! Ich gehe in eine alte indische Stadt. Die Arbeit ist selbstmörderisch, aber es wird dort Gold geben...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Ich habe kein Interesse an Gold. Es wäre mir eine Ehre, Ihnen zu helfen, Kapitän, so wie Sie mir einst geholfen haben. Wann brechen wir auf?";
			Link.l1 = "Gut gesagt, Claude! Sei in voller Bereitschaft - es wird nicht mehr lange dauern.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Kapitän, welche Güter? Wir müssen uns zuerst ein Schiff finden!";
				Link.l1 = "Ja, du hast Recht.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Es wird gemacht, "+GetSexPhrase("Herr","Fräulein")+" Kapitän!";
			Link.l1 = "Ruhig bleiben.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Es wird erledigt, "+GetSexPhrase("Herr","Fräulein")+"Kapitän!";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Kapitän, Sie wissen, ich... Nun, ich würde Sie bitten, mich zu entlassen. Es ist Zeit für mich, mich niederzulassen, zu heiraten und Kinder zu bekommen. Ich habe immer noch kein eigenes Zuhause, wenn ich alt werde, wird niemand da sein, um mir ein Glas Wasser zu bringen.","Kapitän, bitte, lass mich zurücktreten. All diese Jahre habe ich in der ganzen Welt herumgetrieben und ich habe immer noch nichts wirklich gesehen. Ich möchte nur ein neues Leben beginnen, den Anker werfen und die Welt aus einer anderen Perspektive sehen.","Kapitän, der Seefahrtsdienst ist sicherlich eine feine Sache, es gibt guten Gewinn und Abenteuer, aber die Zeit ist gekommen für mich, an mich selbst zu denken. Sie wissen, einen Anker in einem ruhigen Hafen werfen, ein Haus kaufen, Kinder haben. Bitte, lass mich gehen."),LinkRandPhrase("Kapitän, Sie wissen, es tut mir wirklich leid, aber ich habe genug von all diesen Pflichten, Wachen und Disziplin. Sie wissen, ich möchte wenigstens eine Weile ein freies Leben führen, aber ich verstehe, dass Sie nicht auf mich warten werden, also... Könnten Sie mich entlassen?","Kapitän, Sie wissen... Es gibt ein kleines Schiff, das ich mir leisten kann, also... Ich denke, es ist wahrscheinlich an der Zeit, dass ich mein eigenes Geschäft starte. Bitte, könnten Sie mich gehen lassen?","Kapitän, man hat mir gerade eine Stelle im Hafen angeboten. Tatsächlich sehne ich mich schon seit geraumer Zeit danach, den Anker zu werfen und mich auf ein verheiratetes Leben einzulassen. Bitte erlauben Sie mir zu gehen. Ich kann eine solche Gelegenheit wirklich nicht verpassen."),LinkRandPhrase("Kapitän, ich bin wirklich seekrank. Die Ärzte sagen mir ständig, es sei eine Eigenart. Bitte, um Gottes willen, lassen Sie mich gehen, oder ich werde irgendwann einfach über Bord springen.","Kapitän, ich glaube, es ist Zeit für mich, mich niederzulassen und einen ruhigeren Ort zu finden. Sie wissen, ich habe Angst. Angst vor verirrten Kugeln, Angst davor, während einer Entermannung zu sterben. Ich bete zum Herrn, dass er mich am Leben erhält, und wenn ich meine Augen schließe, sehe ich all die unschuldigen Seelen, die ich getötet habe. Sie flehen mich an, sie zu verschonen... Bitte, zeigen Sie etwas Mitgefühl und lassen Sie mich gehen.","Kapitän, meine alten Wunden schmerzen, und die jüngste Prellung erinnert sich jeden Tag an sich. Bald wirst du mich entlassen, und wer wird mich danach einstellen? Bitte lass mich gehen, ich werde mich flicken und einen ruhigeren Ort finden."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Sie alle gehen schließlich. Gut, du bist frei zu gehen.","Ich kann deine Beweggründe verstehen. Früher oder später geht alles zu Ende. Nun, geh dann... und hege keinen Groll, wenn ich dich jemals beleidigt habe.","Schon wieder? Du hast absichtlich den denkbar ungünstigsten Moment gewählt, um mich zu verlassen, nicht wahr? Was auch immer. Lebewohl."),LinkRandPhrase("Schwer zu glauben, was du mir erzählst... Gut, pack deine Sachen und geh.","Du? Ich hätte es nicht erwartet... Nach all dieser Zeit, Seite an Seite kämpfend... Nun, ich halte dich nicht auf. Gott mit dir.","Du klingst ernst. Nun, ich wünsche dir Glück, weiß, dass ich dich vermissen werde."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Ich verstehe... Also so ist es, hm? Und ich habe auf dich gezählt... Nun, wenn du dir bereits sicher bist, dann lass uns unsere Wege trennen. Nimm "+sti(NPChar.rank)*250+" Pesos für Ihre treue Dienste. Und hegen Sie keinen Groll, falls ich Sie jemals beleidigt habe.","Nun, ich trage keinen Groll und erinnere mich an kein Übel. Wenn das deine Entscheidung ist, dann geh. Und nimm "+sti(NPChar.rank)*250+" Pesos, um einen frischen Start zu bekommen, es wird definitiv nützlich sein.","Ich verstehe... Nun, früher oder später musste das passieren. Ich gebe dir "+sti(NPChar.rank)*250+" Pesos, um dein Leben zu regeln. Und kümmere dich auch um deine Gesundheit, der Marine Dienst ist voller Entbehrungen..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("So sagst du... Begreifst du nicht, dass du mir einfach in den Rücken fällst, wenn du jetzt gehst? Ich kann dich jetzt nicht gehen lassen, denk nicht mal dran.","Das sind Neuigkeiten! Du weißt, die Leute sollten mich über solche Dinge vorher informieren! Also vergiss dein Privatleben für eine Weile. Wenn die Zeit gekommen ist, werde ich dir vorschlagen, wann du in den Ruhestand gehen sollst.","Keine Kündigungen. Ich habe jeden im Auge. Ich kann nicht jeden gehen lassen, nur wegen ihres persönlichen Wunsches. Dienet, während ich überlege, ob ihr einen Urlaub verdient.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Danke, Kapitän! Eine wirklich unerwartete Großzügigkeit... Wissen Sie, ich habe noch einige Ihrer Sachen, vielleicht möchten Sie sie zurückhaben?";
			Link.l1 = "Vielleicht... Eine gute Klinge zu finden ist heutzutage nicht so einfach.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, mach dir keine Sorgen. Behalte sie als Andenken an deinen Dienst.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Aber wie so, Kapitän? Selbst die Sklaven werden schließlich an Land geschickt. Und ich bin kein Sklave, also kann ich mein Schicksal selbst bestimmen!","Kapitän, ich habe Ihnen all diese Zeit treu gedient. Habe ich nicht das Recht verdient, über mein Schicksal selbst zu entscheiden?");
			Link.l1 = LinkRandPhrase("Ich sehe, dass ich dich so nicht halten kann. Na gut, wie wäre es mit finanzieller Unterstützung? Das wird nie schaden, du kannst dieses Geld nutzen, um dir ein gemütliches Zuhause in einem ruhigen Hafen zu bauen oder dich um deine Gesundheit zu kümmern.","Gut, lass es uns so sagen. Welche Summe könnte dich dazu bringen, deine Entscheidung zu überdenken?","Du hast recht. Aber was ist mit einer einmaligen Geldzuwendung, würde das deine Meinung ändern?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Oh, nein, mein Freund, hier irrst du dich... Während du deine Zeit in den Tavernen verschwendet und den Röcken nach den Krügen hinterhergejagt hast, konntest du selbst entscheiden, aber sobald du an Bord meines Schiffes getreten bist, hast du dein Schicksal in meine Hände gelegt.","Hmm. Nun, das ist eine ernste Aussage. Anscheinend hast du vergessen, wie ich dich gefunden habe, in einer stinkenden Kneipe ohne einen Pfennig in deiner Tasche. Man kann dir nicht einmal eine einzige Goldmünze zeigen, denn du wirst sie sofort in Rum verwandeln. 'Entscheide über mein Schicksal...' Pfff! Was für ein Witz!"),LinkRandPhrase("Während du in meinem Dienst bist, bin ich es, der Entscheidungen trifft. Und jetzt würdest du bitte zu deinen Pflichten zurückkehren, bevor du mich zu sehr verärgert hast!","Hmm. Nun, das ist eine ernste Aussage. Aber Sie haben das im Voraus gezahlte Geld noch nicht abgearbeitet. Also kann Ihre Demarche als Erpressungsversuch betrachtet werden, nicht wahr?","Oh, ich sehe... Was sagen nochmal die Schiffsvorschriften? Hier, Absatz zwei: 'Wer versucht, ohne Erlaubnis zu gehen, wird auf einer verlassenen Küste gelandet mit einem einzigen Beutel Pulver, einer Flasche Wasser, einer Pistole und einer einzigen Kugel.' Nun, wie würdest du das finden?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Nun, das ist eine andere Geschichte. "+sti(NPChar.rank)*500+" Pesos auf den Nagel, und ich bleibe bei dir.","Nun, vielleicht für "+sti(NPChar.rank)*500+" Pesos könnte ich bleiben, schätze ich.","Nun, wenn du es so darstellst, für "+sti(NPChar.rank)*500+" Pesos, ich könnte meinen Dienst fortsetzen.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("In Ordnung, abgemacht.","In Ordnung. Obwohl du weniger verlangen könntest.","Du hast ja einen ordentlichen Appetit, wie ich sehe! Aber, ich habe dir ein Versprechen gegeben, nicht wahr? Und ich werde zu meinem Wort stehen.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Das ist einfach zu viel. Für diesen Preis könnte ich zwei Offiziere anstellen. Vielleicht ist es einfacher, dich einfach gehen zu lassen.","Nun, du hast sicherlich eine hohe Meinung von dir selbst. Gut, ich lasse dich gehen. Aber du wirst selbst sehen, wenn du ungebunden bist, dass dein Leben nicht so ungetrübt sein wird, wie du erwartet hast.","Ich werde solches Geld nicht bezahlen. Du kannst gehen, aber frag nicht einmal nach Rückkehr, ich vergebe Verrat nicht.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Gut, wenn du es so sagst, bleibe ich. Aber wisse, dass ich damit meinem eigenen Willen widerspreche.";
		Link.l1 = LinkRandPhrase("Sehr gut. Kehren Sie zu Ihren Pflichten zurück, und wir werden dieses Gespräch später fortsetzen.","Kehre zum Schiff zurück. Und denke das nächste Mal nach, bevor du um Ruhestand bittest.","Jawohl. Die Pflicht ist die Pflicht, und du solltest dich noch nicht deinen Fantasien hingeben.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("Ich kann es nicht glauben! Danke Kapitän, es ist eine solche Last von meinem Kopf.","Danke, Kapitän, dass Sie mich nicht festhalten. Sie wissen, ich möchte wirklich andere Dinge im Leben ausprobieren.","Heh, jetzt muss ich mich wohl an meine neu gewonnene Freiheit gewöhnen. Erst jetzt habe ich erkannt, wie überdrüssig ich all diesem Flottendienst war.");	
		Link.l1 = RandPhraseSimple("Nun, viel Glück für dich.","Du bist jetzt frei. Dein Dienst ist vorbei.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitän, ich möchte nicht gegen mein Gewissen handeln und mich am Brigantentum beteiligen.","Kapitän, ich möchte nicht länger an Ihren Ausschreitungen teilnehmen. Ich bin ein Offizier, kein Schlächter.","Kapitän, Ihre Banditenmethoden des Geschäftemachens machen meinen Aufenthalt in Ihrer Mannschaft unmöglich."),LinkRandPhrase("Kapitän, ich muss zugeben, dass meine Anstellung bei Ihnen ein enttäuschender Fehler war. Ich bin nicht bereit, meinen Ruf für irgendein Geld zu opfern.","Kapitän, Sie haben auf Ihrem Schiff alle abscheulichsten Schurken der Neuen Welt versammelt. Für einen anständigen Mann ist es ekelhaft, sie nur anzusehen. Ich möchte nicht mehr mit einer solchen Crew dienen.","Kapitän, Sie haben eine volle Crew von Gaunern angestellt, es gibt nicht einen einzigen anständigen Mann, mit dem man plaudern kann. Ich verabscheue solchen Dienst."))+"Auf Wiedersehen.";
			Link.l1 = "Was?! Das ist ein Kriegsschiff, keine höhere Töchterschule! Du kannst zur Hölle fahren!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Ich wusste, dass du bald gehen würdest... dieser Dienst ist nichts für dich. Aber beschuldige mich nicht. Hier sind "+sti(NPChar.rank)*500+" Pesos, sie werden Ihnen nützlich sein, während Sie nach einem Job suchen, der Ihnen gefällt.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Oh, also singst du jetzt so ein Lied. Und was ist mit deinem Anteil an jedem einzelnen Raubzug, brennen deine Hände? Oder planst du, dich in ein Kloster zurückzuziehen, um um Vergebung deiner Sünden zu beten? Dann sprich auch ein Wort für uns! Ha-ha-ha-ha-ha!","Hmm. Nun, das ist eine ernste Aussage. Und wo hat dein unschuldiges Gewissen hingeschaut, während wir zusammen Händler ausgeraubt haben? Wie willst du es reinwaschen? Oder wirst du uns verpfeifen, damit wir in anständiger Gesellschaft am Galgen hängen?","Oh, bravo! Anscheinend hast du vergessen, wie ich dich gefunden habe, in einer stinkenden Taverne ohne einen Kupfer in deiner Tasche. Zu deiner Information, als Offizier bist du keinen Pfifferling wert. Du bist wertlos!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitän, ich mag eure noblen Spielchen wirklich nicht und ich werde meine Gewohnheiten nicht für eure Ruhe aufgeben. Lebewohl.","Kapitän, ich kann nicht länger in Ihrem Dienst bleiben. Ich habe bereits so viel Zeit verschwendet. Als einfacher Freibeuter hätte ich bereits ein Vermögen gewonnen. Ich gehe.","Kapitän, deine Männer ekeln mich an. Nicht ein einziger anständiger Mann, nur feine Pinkel, keiner, mit dem man einen trinken könnte. Ich gehe."),LinkRandPhrase("Kapitän, ich bin ein Veteranenoffizier und Ihr Schiff sieht mehr wie ein Frachtschiff aus. Ich bin kein Fan von solch einem Dienst. Auf Wiedersehen.","Kapitän, deine gesamte Crew sind lauter feine Pinkel, es gibt nicht einen einzigen Mann, mit dem man trinken oder reden kann. Ich habe eine starke Abneigung gegen solchen Dienst. Lebewohl.","Kapitän, ich dachte, ich würde unter einem echten Korsar dienen, aber alles, was wir tun, ist nur Wohltätigkeit! Ich will meine Zeit nicht weiter verschwenden. Ich gehe."));
			Link.l1 = RandPhraseSimple("Ich verstehe. Angesichts Ihrer Haltung sollte das früher oder später passieren. In Ordnung, ich werde Sie nicht aufhalten.","Deine Aussage war nicht unerwartet. Ehrlich gesagt, bin ich schon seit geraumer Zeit unzufrieden mit deiner Einstellung.")+"Viel Glück.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Ich wusste, dass du bald gehen würdest... dieser Dienst ist nichts für dich. Aber beschuldige mich nicht. Hier sind "+sti(NPChar.rank)*500+" Pesos, sie werden nützlich sein, während du nach einem neuen Job suchst.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. Nun, das ist eine ernste Aussage. Aber du hast das dir im Voraus gezahlte Geld noch nicht abgearbeitet. Also kann deine Demarche als Versuch der Erpressung angesehen werden, richtig?","Oh, ich verstehe... Was sagen die Schiffsvorschriften? Hier, Absatz zwei: 'Wer versucht, ohne Erlaubnis zu gehen, wird auf einer verlassenen Küste gelandet mit einem einzigen Beutel Pulver, einer Flasche Wasser, einer Pistole und einer einzigen Kugel.' Nun, wie würde dir das gefallen?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Versuch nicht mal, mich zu beleidigen! Ich arbeite zwar für Geld, aber ich habe immer noch das Recht, einen Job nach meinem Geschmack zu wählen!","Ich bin ein freier Mann! Und ich habe das Recht, wann immer ich will, einen neuen Job anzunehmen!","Ich bin kein Sklave, der für Essen arbeitet, also ist mein Gewissen rein! Aber ich werde nicht mehr an Raubzügen teilnehmen!");
				Link.l1 = "Nun, tatsächlich liegt ihr falsch... Während ihr in der Taverne trankt, konntet ihr euch jede Arbeit aussuchen, die ihr mochtet... Aber sobald ihr an Bord meines Schiffes getreten seid, wurde euer einziger Rückweg eine Kanonenkugel, die euren Hals zerschmettert... Und mit herausgerissener Zunge, damit ihr in der nächsten Welt nichts ausplaudert...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Also gut. Du kannst gehen... Aber Gott bewahre dich davor, mich auf offener See zu treffen. Ich schwöre, du wirst den Moment bereuen, in dem du dich entschieden hast, nicht an meiner Seite zu bleiben.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Versuch nicht mal, mich einzuschüchtern! Ich arbeite zwar für Geld, aber ich habe immer noch das Recht, mir einen Job auszusuchen, der mir gefällt!","Ich bin ein freier Mann! Und ich habe das Recht, wann immer ich will, einen neuen Job anzunehmen!","Ich bin nicht dein Sklave! Und ich werde nicht weiter ein elendes Leben auf deiner alten Tonne führen!");
				Link.l1 = "Nun, eigentlich liegst du falsch... Als du noch in der Taverne getrunken hast, konntest du dir noch jeden Job aussuchen... Aber sobald du an Bord meines Schiffes getreten bist, wurde dein einziger Weg zurück eine Kanonenkugel, die dir den Hals zerfetzt... Und mit herausgerissener Zunge, damit du in der nächsten Welt nichts ausplauderst...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Also gut. Du kannst gehen... Aber Gott bewahre dich davor, mich auf offener See zu treffen. Ich schwöre, du wirst den Moment bereuen, in dem du dich entschieden hast, nicht an meiner Seite zu bleiben.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Wenn du es so darstellst, werde ich bleiben, ich habe einfach keine andere Wahl. Aber behalte im Kopf, dass ich das nicht aus eigenem Antrieb mache...","Gut, wenn du es so darstellst, bleibe ich. Aber wisse, dass ich damit gegen meinen eigenen Willen handle.");
			Link.l1 = RandPhraseSimple("Das ist in Ordnung... Dienst bis ich entscheide, wann ich dich gehen lasse.","Das ist gut. Bleib bei der Arbeit... Ich entscheide, wann ich dich gehen lasse.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"Du wirst mich niemals dazu zwingen, es zu überdenken! Du hast kein Recht, mich als Sklaven zu halten! Ich werde gehen, halt dich fern oder du bist erledigt.","Glaubst du, du könntest einen erfahrenen Offizier erschrecken?! Mehr als einmal war ich dem Tod nur um Haaresbreite entkommen. Und wenn du es so sagst, ist es viel besser, in einer fairen Schlacht zu sterben, als während einer blutigen Plünderung!");
			Link.l1 = NPCharRepPhrase(NPChar,"Nun... jeder wählt sein eigenes Schicksal. Ich hoffe, du hast deine Gebete gesagt, bevor du zu mir gekommen bist.","Wenn ich gewusst hätte, dass das passieren würde, als ich dich in der Taverne aufgelesen habe, hätte ich dich lieber am Galgen baumeln lassen. Und jetzt ist es nicht zu spät, das zu arrangieren...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Nun, du kannst gehen, wenn du deine Freiheit so sehr brauchst. Aber ich gebe dir keine Empfehlungen.","In Ordnung. Du kannst gehen... Aber Gott bewahre dich davor, mich auf offener See zu treffen. Ich schwöre, du wirst den Moment bereuen, in dem du dich entschieden hast, nicht an meiner Seite zu bleiben.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"Hör schon auf, mich einzuschüchtern! Welcher von deinen Saugern würde es wagen, sich mir entgegenzustellen? Wenn ich Kapitän wäre, würden sie sich schon lange im Geld wälzen! Und nachdem du all diese Wohltätigkeit betrieben hast, fürchtest du, dass deine Mannschaft sich auf meine Seite schlagen wird?!","Lass deine Spielchen, du wirst mich nicht erschrecken! Leb wohl.");
			Link.l1 = NPCharRepPhrase(NPChar,"Nein, Kumpel, du wirst nicht lange genug leben, um zum Galgen zu kommen. Solcher Luxus ist nicht für dich...","Nicht so schnell Kumpel, wir sind noch nicht quitt, du schuldest mir was.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Ich bin der Beste "+XI_ConvertString(Npchar.quest.officertype)+" in diesen Gewässern. "+Npchar.quest.officertype_2+"Und ich bin bereit, Ihnen einen Gefallen zu tun und unter Ihnen zu dienen.","Nun, sie sagen, ich bin nicht schlecht "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Sie können mich auf Ihr Schiff nehmen, Kapitän, und es selbst sehen.");
			Link.l1 = "Und wie viel willst du?";
			Link.l1.go = "price";
			Link.l2 = "Und was für ein Spezialist sind Sie?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Ach, ich habe schon ein "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, Kapitän, die halbe Garnison ist im Moment hinter Ihnen her. Sicherlich ist es nicht die beste Zeit, in Ihrer Crew angestellt zu werden!","Und uns durch die Menge bis zum Schiff kämpfen? Nein, Käpt'n, ein andermal...");
				link.l1 = RandPhraseSimple("Wie du wünschst...","Eigentlich wollte ich dich nicht einstellen."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Haben Sie Ihre Meinung geändert, Kapitän? Haben Sie sich für ein Neues entschieden "+XI_ConvertString(Npchar.quest.officertype)+" würde nicht wehtun?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "So etwas. Wie viel willst du?";
                Link.l1.go = "price";
			}
			Link.l2 = "Und was kannst du?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Ich habe ein volles Set. Wir sehen uns.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Ich denke, wir können uns darauf einigen "+Npchar.quest.OfficerPrice+" Pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Ich denke, wir können uns einigen auf "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" Dublonen.";
			}	
			Link.l1 = "Ist das nicht ein bisschen viel?";
			Link.l1.go = "trade";
			Link.l2 = "Ich stimme zu. Betrachten Sie sich als Teil der Mannschaft.";
			Link.l2.go = "hire";
			Link.l3 = "Du bist dieses Geld nicht wert.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "In Ordnung... Ich denke, ich könnte sogar zustimmen auf "+Npchar.quest.OfficerPrice+" Pesos. Was sagst du dazu?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Ich denke, ich könnte sogar zustimmen auf "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" Dublonen. Was sagst du dazu?";
				}
				Link.l1 = "Jetzt ist es besser. Du bist drin.";
				Link.l1.go = "hire";				
				Link.l2 = "Ich denke immer noch, es ist ein bisschen zu viel. Tschüss.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Es tut mir leid, Kapitän, aber ich bin genau so viel wert, wie ich gefordert habe. Wenn es Ihnen zu viel ist, dann suchen Sie jemand anderen.";
				Link.l1 = "Also gut, ich stimme zu. Ich nehme dich mit.";
				Link.l1.go = "hire";				
				Link.l2 = "Das ist, was ich tun werde. Lebewohl.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Ich sehe, Ihnen fehlt das Geld, Kapitän! Es tut mir leid, aber ich arbeite nicht auf Kredit.";
			Link.l1 = "Oh, Teufel!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Danke, Kapitän. Sie werden Ihre Wahl nicht bereuen.";
				Link.l1 = "Ich hoffe es.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Danke, Kapitän. Sie werden Ihre Wahl nicht bereuen.";
				Link.l1 = "Ich hoffe es.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Ich beende nur noch mein Getränk, Kapitän, und dann gehe ich zum Schiff. Mach dir keine Sorgen, ich werde rechtzeitig dort sein.";
			Link.l1 = "In Ordnung. Wenn du zu spät kommst, lasse ich dich das Deck schrubben!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Kapitän, aber Sie haben kein Schiff!";
				Link.l1 = "Danke, dass du mich daran erinnert hast...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Höchste Aktivität der Ratten auf der Reise "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"%% der Gesamtladungsmenge. Für "+GetCrewQuantity(PChar)+" Seeleute, die wir brauchen werden "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" Nahrung pro Tag. Das berücksichtigt nicht den Transport von Sklaven.";
			Link.l1 = "Danke.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Welche sind Ihre Befehle?";
            Link.l1 = "Steh hier!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folge mir und bleibe nicht zurück!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Ich möchte, dass Sie in einer bestimmten Entfernung zum Ziel bleiben.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Wir müssen die Munitionsart für Ihre Feuerwaffe ändern.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Wir müssen die Munitionsart für dein Musketen ändern.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Wir müssen deine Prioritätswaffe für den Kampf ändern.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Wähle die Art der Munition:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
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
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Wählen Sie den Munitionstyp:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Zu Beginn des Kampfes wirst du folgendes verwenden:";
			Link.l1 = "Klinge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskete";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "Welche Entfernung genau, Kapitän? Geben Sie in Schritten an, aber nicht mehr als 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kapitän, geht es Ihnen gut?";
				link.l1 = "Es tut mir leid, mein Fehler...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Ich werde stillstehen ohne mich zu bewegen. Ist das, was Sie von mir wollen, Kapitän?";
				link.l1 = "Ja. Das ist genau das, was von dir benötigt wird.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Ich glaube, ich habe dir gesagt, dass ich nicht mehr als 20 Schritte vom Ziel entfernt stehen kann.";
				link.l1 = "In Ordnung, haltet die Entfernung von 20 Metern.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Verstanden und berücksichtigt.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Kapitän, obwohl ich Ihre Beweggründe wirklich nicht verstehe, könnten wir darüber am Ufer sprechen? Oder haben Sie sich entschlossen, mich einfach über Bord zu werfen?";
					Link.l1 = "Hmm... Nein, das habe ich nicht gemeint. Bleib hier, bis wir im Hafen ankommen.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Jetzt ist das neu!","Warum, zum Himmel?","Was ist der Grund?!"),RandPhraseSimple("Kapitän, bist du wahnsinnig? Solche Nachrichten ohne Grund zu erzählen!","Wow! Und was habe ich getan, um dich zu verärgern?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Ich habe beschlossen, Ordnung in die Mannschaft zu bringen. Und ich mag deine Beziehungen zu deinen Kollegen nicht","Deine Vorteile waren nicht so gut wie bei der Einstellung besprochen. Also,","Schurken und Taugenichtse in meiner Mannschaft werden nicht bleiben! Also,"),LinkRandPhrase("Es ist zu meinem Wissen gekommen, dass du heimlich Rum stiehlst, meine Crew an hartes Trinken gewöhnst und so die Moral senkst. Daher,","Ich habe genug von deinen Banditenmanieren und ich werde es nicht tolerieren. Also,","Verbringen Sie ständig Ihre Zeit in der Zentralkabine für ein Spiel mit Karten oder Würfeln, das die anderen Offiziere von der Pflichterfüllung ablenkt. Das kann nicht unbegrenzt so weitergehen. Also,"))+"Packe deine Habseligkeiten und verlasse das Schiff.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Darf ich den Grund für eine solche Entscheidung wissen?","Offensichtlich ist eine solche Entscheidung gut begründet?"),RandPhraseSimple("Erkläre dich, Kapitän","Das ist ziemlich unerwartet. Aber ich möchte dennoch den Grund wissen."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Ich bin völlig unzufrieden mit Ihrer Einstellung zu Ihren Pflichten.","Leider warst du kein guter Offizier und wirst es wahrscheinlich auch nie sein...","Du bist ein guter Offizier und dein Dienst war fair, aber nun haben sich unsere Wege getrennt. Frag mich nicht warum."),LinkRandPhrase("Ich habe dich gewarnt, dass die Leidenschaft zum Rum dich zerstören würde. Wie kann ich einem Mann in einem Kampf vertrauen, der nicht einmal in der Lage ist, sein Schwert in die Scheide zu stecken?","Du bist ein schrecklicher Seemann und Offizier... Ich denke, du wirst mehr an Land sein als auf See.","Ich bin nicht zufrieden mit deinen Qualifikationen, aber jetzt habe ich endlich einen anständigen Ersatz gefunden."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... Darf ich den Grund erfahren?","Das ist eine ernste Aussage. Darf ich wissen, mit was genau Sie unzufrieden sind?"),RandPhraseSimple("Erkläre dich, Kapitän.","Offensichtlich ist eine solche Aussage gut begründet?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Ich bin völlig unzufrieden mit Ihrer Qualifikation, daher","Leider haben Sie sich nicht als anständiger Offizier erwiesen. Also,","Ich habe die Nase voll von deinen edlen Manieren. Ich werde sie nicht endlos tolerieren, also"),LinkRandPhrase("Es ist zu meiner Kenntnis gelangt, dass du die Mannschaft zur Ungehorsamkeit aufhetzt. Es wird keine Störungen auf meinem Schiff geben! Und bedank dich nicht, dass ich dich nicht schon früher weggeworfen habe. Also","Deine edlen Prinzipien ehren dich, aber sie stehen im Widerspruch zum Räuberleben eines freien Freibeuters. Also","Ich mag Ihre Beziehung zu Ihren Pflichten nicht. Also"))+"Packen Sie Ihre Sachen und verlassen Sie das Schiff.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitän, das habe ich wirklich nicht erwartet! Vielleicht würden Sie mir erklären, was vor sich geht?","Kapitän, was frisst dich?!","Was meinen Sie damit, Kapitän?!"),RandPhraseSimple("Was zur Hölle, Kapitän?! Alles schien gestern noch in Ordnung zu sein, und jetzt sind wir hier, was ist passiert?","Wahnsinn! Vielleicht würdest du dich erklären?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Du bist ein totaler Faulenzer und nutzloser Idiot, sogar ein Schiffsjunge auf einem Küstenschiff würde es besser machen. Ich habe wegen dir schon zu lange gelitten. Also","Ich habe schon eine Weile darüber nachgedacht, dich zu feuern, und jetzt habe ich endlich einen anständigen Ersatz gefunden. Also","Es ist mir zu Ohren gekommen, dass du heimlich Rum stiehlst, meine Mannschaft an hartes Trinken gewöhnt und so ihre Moral senkst. Deshalb"),LinkRandPhrase("Als ich dich einstellte, hast du geprahlt, du seist der beste Offizier der gesamten Flotte, aber es stellte sich heraus, dass du nur ein Faulenzer bist, also","Ich habe dich gewarnt, dass deine Trinkgewohnheit schlecht enden würde. Warum sollte ich einen nutzlosen Trunkenbold auf meinem Schiff behalten? Also","Anstatt zu dienen, streunst du ständig irgendwo herum oder spielst Karten oder Würfel. Hoffentlich hast du nicht gedacht, dass das ewig so weitergehen könnte? Also"))+"Pack deine Habseligkeiten und verlasse das Schiff.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("So sprichst du jetzt! Na gut, wie du willst. Aber sei dir sicher: Ich werde nicht zu dir zurückkommen, selbst wenn ich vor Hunger sterbe!","Ehrlich gesagt, mag ich eure edlen Spiele auch nicht besonders. Also tschüss...","Oh, fahr zur Hölle! Bleib bei deinen Speichelleckern. Ein 'Held', in der Tat!"),LinkRandPhrase("Eigentlich habe ich es nie gemocht, Ihnen zu dienen... Sie haben dort eine Frachtbarke, kein anständiges Schiff. Eher eine Abschlussschule...","Weißt du, ich habe genug von deiner Mannschaft, alle von ihnen feine Pinkel, nur kleine Kinder, kein einziger echter Mann...","Also gut, Kapitän, wie Sie sagen. Aber Gott weiß, ich habe meine Arbeit gut gemacht..."));
			Link.l1 = "Halt ein. Im Moment kann ich das Schiff nicht ohne einen Offizier verlassen. Aber später werden wir auf dieses Gespräch zurückkommen.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Dann geh in Frieden.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Lass den Kopf nicht hängen. Ich habe für dich eine Abfindung vorbereitet - "+sti(NPChar.rank)*500+" Pesos. Ich hoffe, das klärt alle Fragen.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Entschuldigung! Was meinen Sie mit 'das Schiff verlassen'?! Ich habe meinen Kopf nicht dem Traubenhagel ausgesetzt, nur damit Sie mich nach Belieben rauswerfen können!","Ha! 'Verlassen Schiff'! Glaubst du wirklich, dass ich es dir erlauben werde, mich wegzuwerfen wie ein Kätzchen?!","Ruhig, Kapitän, ernsthafte Leute regeln Angelegenheiten nicht auf diese Weise. Ich lasse mich nicht wie ein Neuling behandeln.");
			Link.l1 = "In Ordnung, du darfst vorerst bleiben - aber nur bis ich einen geeigneten Ersatz finde.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Ich wiederhole, Ihr Dienst ist vorbei. Sie können Ihre Sachen packen.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Lass dich nicht aufregen. Ich habe vorbereitet "+sti(NPChar.rank)*500+" Pesos für dich. Ich hoffe, das klärt alle Fragen.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Eigentlich brenne ich nicht vor Verlangen, hier zu bleiben. Aber ich werde auch nicht ohne Entschädigung gehen!","Nun, ich werde sicherlich nicht auf diesem alten Kutter von dir bleiben, aber zuerst wirst du mich entschädigen!")+" "+sti(NPChar.rank)*1000+" Pesos, und wir werden einander vergessen.";
			Link.l1 = "Ich habe mich etwas aufgeregt... Bitte, akzeptieren Sie meine Entschuldigungen und gehen Sie zurück zu Ihren Aufgaben.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "Wovon redest du von Geld, wenn du immer deinen gerechten Anteil erhalten hast? Das sieht für mich nach Erpressung aus!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "In Ordnung. Gib die Ausrüstung zurück, und dann wirst du bekommen, was du gefragt hast.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Das ist eine andere Geschichte. Lebewohl!";
			Link.l1 = "Ich hoffe wirklich, dass sich unsere Wege nie wieder kreuzen werden.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Betrachten Sie dies als eine Entschädigung für moralischen Schaden. Ich werde eine solche Behandlung nicht dulden und wer es wagt, mich so zu behandeln, wird es bereuen!","Das ist keine Erpressung, sondern eine Entschädigung für diese dumme Zeitverschwendung! Und ich werde sie bekommen, egal was es kostet!","Ich habe zu viel Zeit damit verschwendet, unter so einem Weichei wie dir zu dienen. Ich könnte ein Vermögen machen, indem ich Handelsschiffe plündere. Also möchte ich nur meinen verlorenen Gewinn ausgleichen.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "In Ordnung. Hier ist dein Geld... Und jetzt verschwinde!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Du scheinst zu vergessen, wer du bist! Ich lasse es nicht zu, dass Halbhirne wie du mich anschreien!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Mach weiter, Kapitän! Zeige dich!";
			Link.l1 = "Gott weiß, ich wollte es nicht!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Das ist eine andere Geschichte. Auf Wiedersehen!";
			Link.l1 = "Ich hoffe doch, dass sich unsere Wege nie wieder kreuzen werden.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Nun, es ist entschieden. Lebewohl, Kapitän, und hege keinen Groll...","Schade, Kapitän. Aber Gott weiß, ich habe es versucht. Lebewohl.","Nun, Kapitän, Sie sind wirklich schwer zu erfreuen! Also gut, viel Glück für Sie."),LinkRandPhrase("Schade, Kapitän. Sie wissen, ich habe gerne für Sie gearbeitet.","Ja, Dinge passieren... Aber ich hege keinen Groll. Lebewohl.","Sie sind unfair zu mir, Kapitän. Trotzdem respektiere ich Ihre Entscheidung. Lebewohl."));
			Link.l1 = "Halt ein, ich habe meine Meinung geändert. Lass uns später darüber sprechen.";
			Link.l1.go = "exit_good";
			Link.l2 = "Sei nicht verärgert. Viel Glück dir...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Halt ein... Ich habe dich gut ausgerüstet. Gib sie zurück, ich bin nicht dabei, eine Horde auszurüsten...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Halt ... Ich will dich nicht mit leeren Händen gehen lassen. Hier, nimm "+sti(NPChar.rank)*500+" Pesos. Das wird dir nützlich sein, während du nach einem neuen Job suchst.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Oh, sicher, nimm alles zurück...";
			Link.l1 = "Ich weiß, du verstehst mich richtig...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Danke, Kapitän! Eine wirklich unerwartete Großzügigkeit... Wissen Sie, ich habe noch einige Ihrer Sachen, vielleicht möchten Sie sie zurückhaben?";
			Link.l1 = "Vielleicht... Heutzutage ist es nicht so einfach, eine gute Klinge zu finden...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Oh, mach dir keine Sorgen. Behalte sie als Andenken an deinen Dienst.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("In Ordnung, wie du willst. Aber sei dir sicher: Ich werde nicht zu dir zurückkommen, selbst wenn ich vor Hunger sterbe!!","Kapitän, Ihre Banditenmethoden machen mich auch krank. Früher oder später musste das passieren. Und es besteht keine Notwendigkeit, Gründe zu erfinden.","Bleib bei deinen Halsabschneidern, dann. Ein anständiger Mann würde sein Gesicht nicht einmal in der Messe deines Schiffes zeigen. Was für ein Bordell hast du hier, Gott vergib mir!"),LinkRandPhrase("Ehrlich gesagt, missfiel mir auch mein Dienst unter Dir. Du hast eine ganze Mannschaft von Schurken angeworben, kein einziger anständiger Mann zum Plaudern.","Ja, wenn Sie diese Einstellung zu Ihrer Mannschaft beibehalten, werden Sie bald ganz alleine sein und es wird nicht nötig sein, irgendwelche Gründe zu erfinden.","Unsere Feindschaft ist gegenseitig, und das tröstet mich. Auf Wiedersehen."));
			Link.l1 = "Halt ein. Jetzt ist nicht die beste Zeit für deine Pensionierung. Aber alle Forderungen bleiben bestehen.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Geh, geh. Mir geht's gut ohne deine Vorträge.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Halt ein. Ich gebe dir "+sti(NPChar.rank)*500+" Pesos. Ich will nicht, dass du im Rinnstein stirbst, damit ich mich schuldig fühle.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Nun, danke. Lebewohl...","Vielen Dank für Ihr Verständnis. Viel Glück.","Jetzt sind wir fertig. Viel Glück...");
			Link.l1 = "Ich weiß, dass du mich richtig verstehst.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Aber Kapitän, in diesem Fall bleibe ich auf Grund. Wollt Ihr mich wirklich vom Schiff direkt zum Parvis schicken?","Du bist unfair zu mir, Kapitän. Aber ich werde keinen Groll hegen, wenn ich eine anständige Entschädigung erhalte.","Und das ist dein Dank für all meine Kampfwunden? Nun, ich denke, ich kann nicht ohne finanzielle Entschädigung auskommen.");
			Link.l1 = "Gut, ich habe meine Meinung geändert. Du kannst bleiben, aber wir werden auf dieses Gespräch zurückkommen.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Oh, mach dir keine Sorgen. Hier - "+sti(NPChar.rank)*500+" Pesos. Das wird deine Zeit auf meinem Schiff kompensieren.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Ich gebe dir das Geld. Trotzdem hast du dich dank mir schön ausgestattet, und ich denke, es ist angemessen, die Sachen mir zurückzugeben.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Oh, wirklich? Und was ist mit deinem Anteil, den du regelmäßig erhalten hast?! Ich wusste, dass alles enden wird mit Nörgeln und Betteln um Prämien.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Ich wusste, dass du das sagen würdest, aber du bekommst deine Ausrüstung erst zurück, wenn ich "+sti(NPChar.rank)*1000+" Pesos. Ansonsten kannst du es nur über meinen toten Körper haben!";
			Link.l1 = "In Ordnung, nimm dann dein Geld.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Bist du wahnsinnig oder was?! Eine solche Summe für das zu verlangen, was dir kostenlos gegeben wurde?! Ich sehe jetzt, dass deine Gier eindeutig über dein vorgetäuschtes Wohltun gesiegt hat.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Lass es dir nicht einfallen, mich zu beleidigen! Ich mag vielleicht nicht der Beste in der Marine sein, aber ich bin immer noch ein Kampfoffizier. Und ich werde respektiert, sogar von so einem Tölpel wie du es bist!";
			Link.l1 = "Wenn du es noch nicht verstanden hast, wiederhole ich es noch einmal: Hör auf zu betteln, du bekommst nichts von mir.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Nun, ich werde trotzdem eine Genugtuung bekommen!";
			Link.l1 = "Oh, also das ist eine Herausforderung, nicht wahr? Wie du wünschst dann...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Das ist mein Glück! Ich stecke mein Herz und meine Seele in den Dienst, nur um ohne jegliche Dienstleistung rausgeworfen zu werden!","Welch ein Unglück?! Ich werde eingestellt und dann fast sofort rausgeworfen. Ich habe keine Ahnung, zu welchem Heiligen ich heutzutage eine Kerze anzünden sollte...","Verdammt noch mal! Zum dritten Mal in diesem Jahr gefeuert, alle Male an Montagen. Vielleicht sollte ich mich dem Kapitän nicht präsentieren, wenn ich einen Kater habe."),LinkRandPhrase("Nun, wie du willst. Betet, dass wir uns nie wieder begegnen.","Wie du wünschst. Bedenke jedoch, dass du nie einen besseren Offizier finden wirst.","In Ordnung, Kapitän, wie du sagst. Aber Gott weiß, ich habe meine Arbeit gut gemacht ..."));
			Link.l1 = "Halt ein. Jetzt ist nicht die beste Zeit für deine Pensionierung. Aber alle Forderungen stehen.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Verschwinde jetzt. Und danke Gott, dass ich heute guter Laune bin.","Verschwind jetzt. Du bist so gut ein Offizier, wie Scheiße gut ist, um Kugeln zu machen.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Halt ein. Ich gebe dir "+sti(NPChar.rank)*500+" Pesos. Ich möchte nicht, dass du in der Gosse stirbst, damit ich mich schuldig fühle.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Halt ein... Ich habe dich gut ausgestattet, gib mir meine Sachen zurück.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Oh, danke, Kapitän! Das ist wirklich nett von dir...","Danke für Ihr Verständnis. Viel Glück.","Jetzt sind wir fertig. Viel Glück...");
			Link.l1 = "Viel Glück. Ich hoffe, du verschwendest nicht alles in der ersten Taverne.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("Und jetzt nimmst du auch noch meine Ausrüstung! Ach, zum Teufel damit! Ich geh angeln, das schwör ich...","Ich sehe, dass du dich entschieden hast, mich völlig auszunehmen. Na gut. Jetzt gibt es nur noch einen Weg für mich, zum Vorplatz...","Oh, vielen Dank! Jetzt hast du dich entschieden, mich auszurauben. Oh, welch grausames Schicksal... Nimm es dann, nimm es! Was kann ich sowieso tun...");
				Link.l1 = "Verschwinde jetzt. Du bist so gut ein Offizier, wie Scheiße gut ist zum Kugeln machen.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Wie Sie wünschen, Kapitän, aber bitte seien Sie so nett und geben Sie mir zuerst "+sti(NPChar.rank)*1000+" Pesos. Lassen Sie dies eine Entschädigung für den moralischen Schaden sein.","In Ordnung. Aber ich möchte immer noch erhalten "+sti(NPChar.rank)*1000+" Pesos als Entschädigung für meinen harten und treuen Dienst.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Was für ein Schurke! Also gut, hier ist dein Geld.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Bist du verrückt?! Wagst du es, so viel Geld für das zu verlangen, was ich dir selbst gegeben habe!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ach-ha! Ich habe nur gescherzt! Wie könnte ich einen alten Freund hinauswerfen, so löchrig wie seinen Hut!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Nun, dann bekommst du nichts! Ich mache keinen Schritt, bis ich das Klimpern meines Geldes höre!";
			Link.l1 = RandPhraseSimple("Du wirst bald das Klimpern meiner Klinge hören!","Dann wirst du mit den Füßen voran fortgetragen!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "Was jetzt?! Wir haben bereits über alles gesprochen! Nie wieder werde ich einen Fuß auf dein Schiff setzen.";
			Link.l1 = RandPhraseSimple("Verschwinde jetzt. Nach allem ist es kein großer Verlust.","Also gut, geh dann. Ich werde dich nicht aufhalten.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Gibt es noch etwas, Kapitän? Ich dachte, wir hätten bereits alles besprochen...";
			Link.l1 = "Nein, nichts. Wollte nur Auf Wiedersehen sagen...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Kapitän, wir haben alles besprochen und unsere Forderungen ausgedrückt. Du wirst doch nicht sagen, dass du deine Meinung geändert hast, oder?";
			Link.l1 = "Gut, geh dann. Nicht ein großer Verlust, nach allem.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Kapitän, welche anderen Fragen könnten es geben? Nur um Ihnen zu sagen, ich bin sehr beleidigt und habe keine Lust zurückzukehren...";
			Link.l1 = "Also gut, geh dann. Nicht dass ich dich so sehr gebraucht hätte.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Aye-aye Kapitän!";
		    Link.l1 = "Ruhig bleiben.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Aye-aye Kapitän!";
		    Link.l1 = "Ruhig.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Kapitän! Das wäre eine Ehre!";
            Link.l1 = "Halte Ordnung und lass die Stadt gedeihen, und ich werde von Zeit zu Zeit einlaufen, um die Zölle einzutreiben.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Ich habe meine Meinung geändert.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Welche sind Ihre Befehle? Das letzte Mal, als Sie mich besuchten "+FindRussianDaysString(iTemp)+" vor.";
			}
			else
			{
			    dialog.Text = "Welche sind Ihre Befehle?";
			}

            Link.l1 = "Wie viel Steuergeld hast du "+NPCharSexPhrase(NPChar,"gesammelt","gesammelt")+"an diesem Punkt?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Du wirst auf dem Schiff gebraucht, ich entbinde dich von der Stadtverpflichtung.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Alles Gute.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Meine Fähigkeiten erlauben das Sammeln "+FindRussianMoneyString(iFortValue*iTax)+" Pro Tag. Über "+FindRussianDaysString(iTemp)+" Ich "+NPCharSexPhrase(NPChar,"gesammelt","gesammelt")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Ich will all das eingesammelte Steuergeld nehmen.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Danke für den Dienst!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Großartig! Ich bin kein Landratte, weißt du.";
            Link.l8 = "Das ist gut.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Ich höre dir zu.";
			Link.l1 = "Es geht ums Entern.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Es geht um dein Schiff.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Ich möchte, dass du für eine Weile meine Staffel verlässt und auf eigene Faust Glück suchst.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Bisher nichts.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Also, was ist dein Wunsch.";
			Link.l1 = "Entere keine feindlichen Schiffe. Kümmere dich um dich selbst und die Crew.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Ich möchte, dass du feindliche Schiffe entern.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Also, was ist dein Wunsch.";
			Link.l1 = "Ich möchte, dass Sie Ihr Schiff nach dem Einsteigen nicht gegen ein anderes austauschen. Es ist zu wertvoll.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Wenn du feindliche Schiffe entern, kannst du sie für dich selbst nehmen, wenn sie zufällig anständig sind.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Jawohl, Kapitän.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Es wird erledigt, Kapitän.";
			Link.l1 = "Ruhig bleiben.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye Kapitän.";
			Link.l1 = "Ruhig.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Es wird erledigt, Kapitän.";
			Link.l1 = "Ruhig bleiben.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Kapitän, ich werde Ihre Geschwader nicht verlassen, weil Sie bereits drei Schiffe entlassen haben.";
					Link.l1 = "Ja, vielleicht hast du recht.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Kein Problem, Kapitän. In welcher Stadt sollen wir uns treffen?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Ich habe meine Meinung geändert.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Kapitän, aber ich kann nicht auf Sie in der Kolonie warten, die uns feindlich gesinnt ist!";
				Link.l1 = "Weißt du, vergiss all diese Reisen...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Käpt'n, wir haben kaum noch Matrosen in der Crew! Von welcher Reise sprichst du?!";
				Link.l1 = "Das stimmt, uns fehlen wirklich Seeleute...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Käpt'n, ich habe nicht genug Proviant an Bord für so eine Reise.";
				Link.l1 = "Ja, du hast recht. Die Reise kann warten...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Kapitän, aber mein Schiff ist in einem schlechten Zustand. Es wäre unklug von mir, unter solchen Umständen alleine in See zu stechen!";
				Link.l1 = "Ja, du hast recht. Dein Schiff braucht eine Reparatur.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Ich verstehe. Bis "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" zu gehen "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" Tage, was mache ich bei der Ankunft?";
				Link.l1 = "An der Hafenkolonie für einen Monat liegen bleiben.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Du weißt, ich habe es mir überlegt. Bleib bei mir...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Ich verstehe, Kapitän. Ich werde sofort aufbrechen.";
				Link.l1 = "Ja, bitte tun Sie das.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Heute werde ich wieder in See stechen...","Vergiss nicht unser Treffen in "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Das")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Ich würde es auch mögen. Von nun an steht mein Schiff wieder unter deinem Kommando, Käpt'n.";
					Link.l1 = "Gut.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Käpt'n, du hast bereits fünf Schiffe in deinem Geschwader - was wirst du mit dem sechsten machen? Nun, ich denke, ich warte lieber hier auf meinem Schiff auf dich. Deine neuen Gefährten scheinen mir nicht zuverlässig zu sein. Ihre Schiffe werden bald sinken, und du wirst für mich zurückkommen.";
					Link.l1 = "He, bist du nicht schlau? Du solltest ein Admiral sein, nicht nur ein Kapitän!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, Kapitän, du bist zurückgekehrt, genau wie ich es gesagt habe. Also, ist jetzt ein Platz in deinem Geschwader frei?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Ja, "+NPChar.name+", da ist einer. Willkommen in der Staffel.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Noch nicht, leider.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Kapitän, die Dinge sind Scheiße! Der Feind hat uns fest im Griff, ich fürchte, sie lassen nicht locker, bis wir tot sind! Unsere Leute stecken gerade in echten Schwierigkeiten, und die meisten Kanonenbesatzungen sind außer Gefecht!";
			link.l1 = "Ich werde ihnen helfen. Übernimm das Kommando und bring uns hier raus!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Ja, Herr!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Sieg, Kapitän! Die Landungspartei wurde vernichtet, der Feind hat sich zur Rückzug entschieden und ist nach Süden abgezogen. Der Zustand des Schiffes ist akzeptabel. Lebende Besatzung: "+GetCrewQuantity(pchar)+" Leute. Bericht abgeschlossen!";
			link.l1 = "Danke! Rum für alle und verstärkt die Wache, bis wir den Hafen erreichen!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Hurra! Jawohl!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}
