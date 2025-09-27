// Орели Бертин - просто жительница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nem akarok veled beszélgetni. Ok nélkül békés civileket támadtok meg, és harcra provokáljátok ôket. Tûnjetek el!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Jó napot, uram. Mit mondasz?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+", én egy újonc vagyok itt, így most ismerkedem a helyiekkel.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Akarsz valamit?";
				link.l1 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Csak tudni akartam, hogy vagy. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Értem. A nevem Orelie Bertine. Hogy kerültél ide?";
			link.l1 = "Mondjuk úgy, hogy csak látni akartam a misztikus Igazság Szigetét.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Szóval te is azok közé az ôrültek közé tartozol, akik önszántukból jönnek ide... Nos, most már lesz elég idôd, hogy megnézd a szigetet, és hogy bôségesen egyél a 'justice'.";
			link.l1 = "És a szarkazmusod szerint van valami probléma az igazságossággal?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Nem, minden rendben van. De valamiért fizetnünk kell a kalózoknak az ételért, ami nem is olyan régen még ingyen volt mindenkinek. És amikor a klánok harcolni kezdenek a szigetünkön, nekünk a hajókban kell ülnünk, hogy elkerüljük, hogy lelôjenek vagy lemészároljanak minket\nÚgy értem, hogy a mi területünkön azt csinálhatnak, amit akarnak, de mi nem tehetjük ugyanezt az övékén. De semmi baj, nincs több baj...";
			link.l1 = "Értem. Rendben, örülök, hogy találkoztunk. Viszlát!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Hallgatlak.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Régóta élsz itt?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Van valami érdekes a szigeten?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mit gondolsz a klánokról?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Zavarnak a kalózok?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Már nagyon régóta. Már vesztettem a számolásomban. Tizenhét éve lehet... nem, talán tizennyolc... vagy húsz? Mi az aktuális évszám?";
			link.l1 = "Értem... Szóval te már régóta itt vagy?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Viszonylag. Még emlékszem azokra az idôkre, amikor a kalózok kereskedtek velünk, és a legvakmerôbb és legokosabb narválok a szárazföldre vitorláztak, hogy a hajók' rakterébôl származó árukért cserébe ellátmányt cseréljenek. De sokan vannak, akik soha nem láttak más helyet, csak a Szigetet, mert itt születtek. Ôk nem csak régiek itt, hanem ôslakosok.";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Igen, így van. Itt minden érdekes. Sétálj körbe és nézd meg magad. Ússzon körbe a Sziget középsô részén. Látogasson el egy kocsmába, egy boltba és egy templomba. A probléma az, hogy az érdeklôdés egy héten belül visszaesik, ezt megígérhetem.";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "És hogyan gondoljunk azokra a banditákra? Próbálok távol maradni tôlük, ennyi az egész. A narválok legalább valami jót tesznek a Szigeten, nagyon tehetséges mesteremberek vannak közöttük, de a rivadók csak barbárok és pogányok\nMég mindig az afrikai törvényeik szerint élnek, mint több száz évvel ezelôtt. Állatok. Az egyetlen dolog, amit megtanultak, az a lôfegyverhasználat. Azt mondják, hogy kannibalizmus rituálékat követnek el!";
			link.l1 = "Micsoda rémálom...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Az a rész, amikor eladják nekünk a saját élelmiszereinket, egy kicsit zavaró, de nem ártanak a polgároknak. Épp ellenkezôleg, rendet tesznek a klánokban, és megakadályoznak minden erôszakot\nVolt egy polgár, aki gondot okozott és a szablyáját lóbálta. Két másik helybélit meg is sebesített. A kalózok néhány hétre a Tartaroszba vitték. Most a férfi nyugodt és békés. Nem látjuk gyakran, a külsô gyûrû az új otthona...";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "A francba!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Mi?! Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!";
			link.l1 = "Ostoba lány!";
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
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha a férfiak fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Elviszem.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
