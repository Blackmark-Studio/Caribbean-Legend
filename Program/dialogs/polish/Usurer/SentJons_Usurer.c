// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi to pytanie niedawno...","Tak, pozwól, że zgadnę... Znowu krążysz w kółko?","Słuchaj, ja tu zajmuję się finansami, nie odpowiadam na pytania...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam w tej chwili nic do omówienia."),"Umph, gdzie się podziała moja pamięć...","Zgadłeś, przepraszam...","Rozumiem...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Chciałbym porozmawiać z tobą o jednym z twoich dłużników.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Który?";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Honor) To na pewno Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Honor) Masz czelność rozmawiać ze mną tak spokojnie. Wysłałeś łowców nagród za moim człowiekiem.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie? Ależ on już nie jest moim dłużnikiem. Jego dług został spłacony dawno temu, sir.";
			link.l1 = "Naprawdę? Przez kogo, jeśli to nie tajemnica?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "To nieprawda. Przez jego kapitana, Richarda Fleetwooda. Prawdziwy dżentelmen, każdy powinien mieć takich przyjaciół jak on.";
			link.l1 = "Widzisz, teraz jestem kapitanem Charliego. Pan Fleetwood... przetransferował go do mojej służby. Dobrze wiedzieć, że dotrzymał obietnicy i ci zapłacił.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Więc dlatego pytasz.";
			link.l1 = "Nie tylko to. Znasz dobrze Charliego, prawda? Został aresztowany, a wcześniej wysłano za nim najemników. Masz pojęcie dlaczego? W końcu masz do czynienia z bardzo... różnorodnym kręgiem ludzi.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie aresztowany? Zaskoczył mnie pan, sir, nic o tym nie wiedziałem. Ani o jego... wrogach. Dobry, bogobojny człowiek jak on...";
			link.l1 = "Nie da się z tym spierać. Cóż, mimo wszystko dzięki. Mam nadzieję, że komendant przyjmie ode mnie kaucję.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "Nie wahaj się podejść do mnie ponownie, jeśli potrzebujesz funduszy na zabezpieczenie kaucji - dam ci dobre warunki.";
			link.l1 = "Ha-ha, czy ty poważnie? Lichwiarz zawsze będzie lichwiarzem. Mogę sobie pozwolić na kaucję sam. Do widzenia.";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "Łowcy nagród? Za twoim człowiekiem? O czym ty mówisz?..";
			link.l1 = "Nie zaprzeczaj. Lepiej się przyznaj, a załatwimy to po dżentelmeńsku. Ale jeśli będziesz udawać głupka, będę musiał załatwić to z tobą w trudny sposób.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "Musisz się mylić!.. Straż!!! Grozi mi śmiercią!";
			link.l1 = "O kurwa mać...";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(15)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
