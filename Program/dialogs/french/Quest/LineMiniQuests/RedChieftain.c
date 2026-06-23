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
			dialog.text = "Ceci est un bug. Faites-le savoir aux développeurs.";
			link.l1 = "Je le ferai !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "RedChieftain":
			dialog.text = "Comment, visage pâle. Je vois que tu es capitaine d'une grande pirogue. Moi Kanauri. Je suis le chef des Caïmans - la puissante tribu Arawak. Moi vouloir parler avec toi.";
			link.l1 = "Je vous écoute, chef. Quels soucis vous amènent à moi ?";
			link.l1.go = "RedChieftain_0";
			link.l2 = "Que veux-tu de moi, sale singe à la peau rouge? Retourne dans tes jungles et ne me dérange pas avec tes requêtes.";
			link.l2.go = "RedChieftain_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
		break;
		
		case "RedChieftain_exit":
			dialog.text = "Gu-u! Le capitaine blanc n'a-t-il pas été éduqué à être poli? On m'a fait une offre. Vous gagnez beaucoup de wampum mais maintenant je pars. Adieu, visage pâle.";
			link.l1 = "Va, va-t'en...";
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
			dialog.text = "Frère blanc perspicace comme hibou, rusé comme serpent. Malheur arrive à l'Indien. Grande-grande pirogue d'hommes blancs vient à mon village. Ils prennent beaucoup de Cayman, mon peuple, les mettent sur leur pirogue et les emmènent à Mère de Toutes les Eaux...";
			link.l1 = "Attends... es-tu en train de dire que ton peuple a été réduit en esclavage par des hommes blancs d'un navire ?";
			if (int(pchar.Basenation) == SPAIN) link.l1.go = "RedChieftain_2";
			else link.l1.go = "RedChieftain_1";
		break;
		
		case "RedChieftain_1":
			dialog.text = "Tu parles vrai, frère blanc. Je sais que ces visages pâles ne sont pas tes amis. Ces cruels hommes blancs de la tribu espagnole. Ils prennent mon peuple. Mais je les trouve. Les Espagnols font travailler les Indiens du lever au coucher du soleil, plongent dans la Mère des Eaux, trouvent des coquillages remplis de larmes des dieux.";
			link.l1 = "La plongee perliere... C'est un travail brutal.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Spa = "true";
			pchar.questTemp.RedChieftain.AttackNation = SPAIN;
		break;
		
		case "RedChieftain_2":
			dialog.text = "Tu dis vrai, frère blanc. Je sais que ces gens ne sont pas tes amis. Ils sont de la tribu anglaise. Ils prennent mon peuple. Mais je les trouve. Les Anglais forcent les Indiens à travailler du lever au coucher du soleil, à plonger dans la Mère des Eaux, à trouver des coquillages remplis des larmes des dieux.";
			link.l1 = "La plongee perliere... C'est un travail ardu.";
			link.l1.go = "RedChieftain_3";
			pchar.questTemp.RedChieftain.Eng = "true";
			pchar.questTemp.RedChieftain.AttackNation = ENGLAND;
		break;
		
		case "RedChieftain_3":
			dialog.text = "Indien malade et meurt de l'esclavage. L'homme blanc n'a pas de pitié pour l'Indien. Le fouet et le pistolet sont la loi du blanc pour l'Indien. Moi vieux. Pas d'hommes pour combattre. Les Arawaks de Cayman sont un peuple paisible, nous avons inventé le calumet de la paix. Je te demande, frère blanc, de dégainer le fouet et le pistolet contre le méchant blanc, sauve les Indiens Arawaks.";
			link.l1 = "Me demandes-tu de declarer la guerre ? Tu dois comprendre, chef, mes ressources sont limitees.";
			link.l1.go = "RedChieftain_4";
		break;
		
		case "RedChieftain_4":
			dialog.text = "N'allez pas en guerre. Libérez l'Indien. Mon peuple. Nous vous donnerons toutes les larmes des dieux que nous avons sur les canoës. Tuez le méchant blanc, aidez l'Indien, obtenez les larmes des dieux, vendez-les pour beaucoup-beaucoup de wampum. Tas de wampum";
			link.l1 = "Ah, je vois maintenant. Non, Canauri, je ne peux pas t'aider. Je ne peux pas le faire maintenant - mon navire a besoin de réparations, il ne reste plus de provisions...";
			link.l1.go = "RedChieftain_wait";
			link.l2 = "Dans ce cas, ce serait mon plaisir. Discutons des détails. Où sont vos gens ? Vous avez dit que vous les aviez déjà trouvés...";
			link.l2.go = "RedChieftain_5";
		break;
		
		case "RedChieftain_wait":
			dialog.text = "Gu-u ! Je peux attendre, frère blanc... Je serai dans ce port une lune de plus, à la recherche du protecteur de mon peuple. Tu me trouveras ici quand tu seras prêt.";
			link.l1 = "... ";
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
			dialog.text = "Tu es de retour, frère blanc? M'aideras-tu à punir les hommes mauvais et à sauver l'Indien?";
			link.l1 = "Prêt comme je le serai jamais.";
			link.l1.go = "RedChieftain_wait_4";
			link.l2 = "Je dois encore me préparer.";
			link.l2.go = "RedChieftain_wait_3";
		break;
		
		case "RedChieftain_wait_3":
			dialog.text = "Je serai ici, frère blanc.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "RedChieftain_wait_2";
		break;
		
		case "RedChieftain_wait_4":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(pchar.questTemp.RedChieftain.StartCity);
			dialog.text = "Je suis très heureux que tu aies accepté, frère blanc !";
			link.l1 = "Parlons des détails, Canauri. Où sont tes hommes ? Tu as dit que tu les avais déjà trouvés...";
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
				dialog.text = "Ils sont au camp à Carupano Cove près du camp espagnol appelé Cumana. Chaque jour, ils naviguent sur des bateaux en mer, plongent dans l'eau, très-très profond...";
				link.l1 = "Je vois. Et les Espagnols veillent sur eux pendant qu'ils plongent ?";
				link.l1.go = "RedChieftain_6";
			}
			else
			{
				AddMapQuestMarkShore("Shore54", true);
				pchar.questTemp.RedChieftain.Island = "SantaCatalina";
				pchar.questTemp.RedChieftain.Shore = "Shore54";
				pchar.questTemp.RedChieftain.Add1 = "English";
				pchar.questTemp.RedChieftain.Add2 = "Cape Perlas, not far from Blueweld";
				dialog.text = "Ils font campement au Cap Perlas près d'un camp anglais appelé Blueweld. Chaque jour, ils naviguent sur des bateaux en mer, plongent dans l'eau, profond-profond...";
				link.l1 = "Je vois. Et, bien sûr, les Anglais veillent sur eux ?";
				link.l1.go = "RedChieftain_6";
			}
		break;
		
		case "RedChieftain_6":
			dialog.text = "Oui, deux grands canoës de visages pâles avec des bâtons de feu et de grands couteaux. Le camp sur la rive est également gardé - l'Indien ne peut pas s'échapper.";
			link.l1 = "Quel genre de navires ? Peux-tu les décrire ? Quelle est leur taille ? Quel type de voiles ?";
			link.l1.go = "RedChieftain_7";
		break;
		
		case "RedChieftain_7":
			dialog.text = "Ce canoë est grand, mais Canauri en a vu de plus grands. La voile avant est très-très inclinée, fait trois côtés comme ceci. (Il dessine trois voiles latines et une voile trapézoïdale dans la terre) Le haut est étroit, le bas est large.";
			link.l1 = "Ça ressemble à une goélette...";
			link.l1.go = "RedChieftain_8";
		break;
		
		case "RedChieftain_8":
			dialog.text = "Canauri ne connaît pas ce mot. Visage pâle très prudent s'ils voient une autre pirogue - ils débarquent Indien et attendent que l'autre pirogue s'éloigne.";
			link.l1 = "Fils de pute prudents... comment puis-je m'approcher d'eux ?";
			link.l1.go = "RedChieftain_9";
		break;
		
		case "RedChieftain_9":
			dialog.text = "Si le frère à peau pâle prend une petite pirogue, alors il peut se faufiler près du rivage. Je montrerai le chemin. Mais n'apporte qu'une seule petite pirogue ou le chien à peau pâle verra et chassera l'Indien du bateau dans la jungle...";
			link.l1 = "Compris. J'aurais besoin d'un lougre ou d'une chaloupe pour cette opération. Parfait. Une chaloupe contre deux goelettes... Mon Dieu... et dire que je pensais que cela allait être facile !";
			link.l1.go = "RedChieftain_10";
		break;
		
		case "RedChieftain_10":
			dialog.text = "Allons-nous, frère blanc ? Nous avons moins d'une lune.";
			link.l1 = "Oui. Montez à bord de mon navire, chef. Ne perdons pas de temps !";
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
			dialog.text = "Merci, frère blanc ! Tu sauves la tribu Arawak de Cayman ! Nous te devons une grande dette. Le chemin est libre du chien pâle et l'Indien peut courir librement dans les jungles. Nous te donnons toutes les larmes des dieux laissées sur les bateaux.";
			link.l1 = "Eh bien, voyons ce que tu as...";
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
			dialog.text = LinkRandPhrase("Je suis heureux que les larmes des dieux soient tiennes, frère d'Arawak !","Merci, visage pâle courageux !","Prends notre prise, frère blanc !");
			link.l1 = LinkRandPhrase("Ravi de vous aider !","Merci, frère à la peau rouge!","Génial !");
			link.l1.go = "exit";
			pchar.questTemp.RedChieftain.Ind = int(pchar.questTemp.RedChieftain.Ind)+1;
			AddDialogExitQuest("RedChieftain_Pearl");
		break;
		
		case "RedChieftain_final":
			chrDisableReloadToLocation = false;//открыть локацию
		// belamour legendary edition -->
			if(int(pchar.questTemp.RedChieftain.Tartane) > 5)
			{
				dialog.text = "Merci encore, frère au visage pâle ! Tu as sauvé toutes les pirogues avec l'Indien ! Pour Canauri, il est très important de sauver toutes les pirogues car tu as aussi sauvé le petit-fils de Canauri, que le méchant visage pâle a emmené en esclavage. Enfant, mon petit-fils aimait beaucoup nager, et Kanauri lui a donné cet amulette enchantée pour qu'il ne se noie pas. Maintenant, le petit-fils ne veut plus nager et me donne l'amulette pour que je puisse te la donner, frère au visage pâle. J'espère que les larmes des dieux et ce cadeau seront une récompense suffisante pour la vie d'un Arawak. Et maintenant, nous disons adieu - il est temps pour nous de retourner dans notre village natal.";
				link.l1 = "Bonne chance, Cunauri ! Heureux que votre petit-fils ait survécu ! Je prie pour que ce mal ne vous atteigne plus jamais !";
				link.l1.go = "RedChieftain_final_1Obereg";
			}
			else
			{
				dialog.text = "Canauri te remercie encore, frère au visage pâle ! J'espère que les larmes des dieux seront une récompense suffisante pour la vie des Indiens. Maintenant au revoir, nous retournons au village natal.";
				link.l1 = "Bonne chance, Cunauri ! Ne retombe jamais dans l'esclavage !";
				link.l1.go = "RedChieftain_final_1";
			}
			if(SandBoxMode)
			{
				//if(CheckAttribute(pchar,"questTemp.SanBoxTarget"))
				//{
					//if(int(pchar.questTemp.SanBoxTarget) == 2 ||  int(pchar.questTemp.SanBoxTarget) == 5)
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
