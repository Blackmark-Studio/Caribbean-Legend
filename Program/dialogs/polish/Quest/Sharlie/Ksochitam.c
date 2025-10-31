// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czy czegoś chcesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Ty... wciąż... musisz... umrzeć. On przyjdzie... i cię zabije... tak jak zabił nas wszystkich... tak jak zabił każdego tutaj...";
			link.l1 = "Co? Kim jesteś? O kim mówisz?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "On jest olbrzymi... jest niewrażliwy... zabija... zabije cię. Muszę cię zabić... jeśli cię zabiję, nie staniesz się taki jak my... nie rozumiesz... zginiesz od jego miecza... zamienisz się w to, czym my jesteśmy... jak wszyscy na 'Santa Quiteria'...";
			link.l1 = "Nie ma mowy!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Czekałem na ciebie tak długo!..";
			link.l1 = "Ehm!.. Oszałamiające!... Toż to szkielet, jakiego świat nie widział!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Widzę to... Czuję to... Przyniosłeś mi... moją wolność...";
			link.l1 = "O czym ty mówisz? Czym jesteś?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Jam jest Strażnik Ksocheatem, opiekun maski Kukulkana... i twój niechybny koniec!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Czekaj...";
			link.l1 = "A dlaczego miałbym to zrobić, co? Brak ci tchu, kościotrupie?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Nie. Nigdy nie będziesz w stanie mnie zabić. Nawet tym magicznym sztyletem. Nasz pojedynek może trwać bardzo, bardzo długo, aż całkowicie opadniesz z sił i umrzesz.";
			link.l1 = "Czyżby? A dlaczego nie możesz mnie uderzyć?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Jesteś odważnym, silnym wojownikiem i dzierżysz Pazur Wodza. Jestem zobowiązany pozwolić ci żyć, bo ten, kto posiada ten sztylet, kto odważy się stanąć przeciwko mnie w walce, otrzymuje to, po co przyszedł.";
			link.l1 = "Kim jesteś? Kim naprawdę jesteś, Strażniku?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Nazywano mnie Alberto Casco. Byłem żołnierzem w oddziale Alonso de Maldonado. Znaleźliśmy starożytne Tayasal, ale zostaliśmy schwytani i złożeni w ofierze. Z powodu mojego wzrostu i siły pogański kapłan - Kanek, uczynił mnie Strażnikiem Ksocheatem, stróżem maski Kukulkana. Każdy, kto kiedykolwiek stanął na Ksocheatem, został przeze mnie odnaleziony i zmasakrowany moją ręką, a następnie przemieniony w nieumarłego.\nSztylet Szpona Wodza posłużył do wycięcia mapy tego miejsca z mojego ciała. Będę strzegł bezpieczeństwa maski na zawsze i nie zaznam spokoju, dopóki nie będę trzymał tego sztyletu w moich rękach.";
			link.l1 = "Potrzebujesz Pazura Wodza?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Tak. Skoro potrzebujesz maski. Daj mi sztylet. Odnajdę swoje długo oczekiwane ukojenie, a ty otrzymasz maskę. Przysięgam ci, że będziesz mógł ją zabrać i opuścić Ksocheatem żywy.";
			link.l1 = "Przyjmuję twoją ofertę, Strażniku. Widziałem maskę na tym piedestale za fontanną chrzcielnicy. Czy to ona?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "Tak jest. To potężny artefakt samego Kukulkana, latającego węża. Po zakończeniu naszej rozmowy możesz podejść tam i ją wziąć.";
			link.l1 = "Cóż, mam nadzieję, że dotrzymasz słowa, Strażniku...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "Przysiągłem...";
			link.l1 = "W takim razie weź Szpon Wodza. Mam nadzieję, że przyniesie spokój twojej duszy.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Przekazałeś Szpon Wodza");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "O, jak długo czekałem na ten moment! Teraz mogę wreszcie odejść... Ale na pożegnanie chciałbym przekazać ci cząstkę mojej mocy. To będzie ostatni prezent, jaki kiedykolwiek da Alberto Casco.";
			link.l1 = "... ";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Teraz nadszedł czas, abym odszedł. Nie zwlekaj, bez swojego Strażnika i maski Kukulkana, wyspa wkrótce zniknie na zawsze.";
			link.l1 = "Nie ma czego żałować. Jedno piekielne miejsce mniej na świecie... Ale czekaj, Strażniku! Byłeś w Tayasal! Proszę, powiedz mi, co to za miejsce.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "To stare miasto Majów. Jego wygląd zachował się od czasów, gdy ludzie jeszcze tam mieszkali. Majestatyczne świątynie, wysokie piramidy... Teraz mieszka tam plemię Itza, twierdząc, że są bezpośrednimi potomkami Majów. Starają się naśladować ich we wszystkim: w religii, kulturze i stylu życia.";
			link.l1 = "Jak mogę się tam dostać?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Naszym dowódcą był Alonso de Maldonado. Po prostu podążaliśmy za nim przez dżunglę. Pamiętam tylko, że wysiedliśmy w zatoce Amatique, na północ od Przylądka Pereł, i ruszyliśmy w głąb selwy na Zachód.";
			link.l1 = "Co jest godnego uwagi w Tayasal?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Wszystko tam jest godne uwagi. Absolutnie wszystko. Ale interesowały nas tylko skarby Majów. I znaleźliśmy je. I zapłaciliśmy za nie drogo, zwłaszcza ja. Ale teraz jestem wreszcie wolny!";
			link.l1 = "Co muszę wiedzieć, zanim wyruszę do Tayasal?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Lud Itza posiada wielką siłę i spryt. Nienawidzą białych ludzi bez względu na ich narodowość i zniszczą każdego, kto wtargnie na ich terytorium. Prości wojownicy Itza nie będą wdawać się w jakiekolwiek rozmowy, ale Kanek lub jego syn Urakan, jeśli zobaczą maskę... mogą to zrobić. Jeśli uda ci się dotrzeć żywym do Tayasal, sam się przekonasz. Ale czy będziesz w stanie stamtąd wyjść...";
			link.l1 = "Czy Kanek składa w ofierze wszystkich białych ludzi, którzy przybywają do Tayasal?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Tak bym przypuszczał. Ale to może nie dotyczyć człowieka, który nosi maskę Kukulkana.";
			link.l1 = "Dobrze. Będę na to liczył.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Żegnaj, żołnierzu. Mam nadzieję, że użyjesz mocy maski w słusznym celu.";
			link.l1 = "Żegnaj, Alberto. Z Bogiem.";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
