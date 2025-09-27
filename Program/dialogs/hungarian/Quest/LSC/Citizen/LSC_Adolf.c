// Адольф Барбье - авантюрист
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
				dialog.text = "Helló, helló... Még nem láttalak. Mostanában?";
				link.l1 = "Úgy érti, hogy mostanában a Szigeten? Igen, igazad van. A nevem "+GetFullName(pchar)+", tengerész és kalandor.";
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
			dialog.text = "Ha, pont mint én. Bár nem vagyok tengerész, de a kalandok iránti szenvedélyem ide vezetett. Most a hajó temetôjében kell megrohadnom, mint a többieknek. Egyébként a nevem Adolf Barbier.";
			link.l1 = "Örülök, hogy megismerhettem, Adolf. Viszontlátásra.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Mi a fenéért hatoltál be a lakásomba az engedélyem nélkül?";
			link.l1 = "Rossz modort tanúsítasz a vendégeddel szemben, Adolf. És van egy üzletem a számodra.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Nem üzletelek olyan emberekkel, akiket nem ismerek! Kifelé!";
			link.l1 = "Csak így? Szóval a narválokkal üzletelsz, de velem nem? Szégyen...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "Mirôl beszélsz, bolond? Milyen üzletrôl Narwhals-szal? Ez az utolsó esélyed, hogy eltûnj innen, vagy én magam foglak kidobni!";
			link.l1 = "Nincs hozzá tököd, 'dobásmester'... Most figyelj rám. Hol van a stutzen, amivel le akarod lôni az admirálist? Megmondod magad, vagy legyek meggyôzôbb?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "Micsoda? Milyen stutzen? Milyen admirális? Megôrültél, haver? Eladtam a stutzenemet, és már nincs meg. És nem a te dolgod, hogy kinek adtam el. Leszarom, hogy mit csinálnak vele. És nem fogok lelôni senkit - sem admirálisokat, sem tábornokokat. Megértettél, te faszfej?";
			link.l1 = "Csak azt értem, hogy hazug vagy és gyilkos, Adolf. Tudom, hogy nem eladtad, hanem kiváltottad. Azt is tudom, hogy hatalmas összeget kaptál, hogy visszafizesd az adósságaidat, és hogy megvehesd ezt a kunyhót...";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "Ez az én pénzem, te barom! Megdolgoztam érte! És eladtam a stutzenemet!";
			link.l1 = "Hazudsz, Adolf. Téged a narválok béreltek fel, hogy lôdd le az admirálist. Ôk adtak neked pénzt, hogy kiváltsd a stutzenedet. Ezt a helyet is ôk fizették ki. Te jobban tudod, mint én, hogy az ajtó mögötti bowsprit az egyetlen hely a szigeten, ahonnan a cápa rezidenciájának hátsó erkélyére lehet lôni.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Megôrültél, te barom! Azonnal el kell szigetelni! Már fél éve vártam erre a kabinra, mielôtt Sessile elment innen...";
			link.l1 = "Elég legyen! Átkutatom magát és a kunyhóját, megtalálom a stutzen és még néhány bizonyítékot, ebben biztos vagyok. Aztán együtt megyünk a Cápához. Örülni fog, ha a szemedbe nézhet.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, maga egy beteg állat! Inkább meghalok, minthogy hagyjam, hogy valami ôrült söpredék hozzányúljon a holmimhoz!";
			link.l1 = "Akkor az engedélyed nélkül fogom megérinteni ôket...";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Nos, akkor beszélgessünk. Mit akarsz tudni?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Mit tudsz mondani a helyi klánokról?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Felfedezted már a hajók külsô gyûrûjét?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Van a szigetnek valamilyen kapcsolata Kubával vagy Main-nal?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Találtam egy tengerész - Alvarado, spanyol volt - kéziratát. Rengeteg részlettel írta le a szigetet. Említett néhány érdekes hajót - San Augustine, San Geronimo és Tartarus. Mindannyian de Betancourt hajórajához tartoztak, amely több mint ötven évvel ezelôtt tûnt el\nKutatást végeztem arról az expedícióról. Kiderült, hogy volt egy negyedik hajó, a Szent Anna, amely a század kincstárát szállította - egy halom dublont! Emellett a hajók rakterében aranyérc volt. Úgy döntöttem, hogy megkeresem a szigetet\nmegállapodtam egy ismerôs kapitánnyal, és elhajóztunk a szkúnáján. Azt hiszem, világos, hogyan végzôdött a történet. Megtaláltuk a Szigetet, Betancourt hajóit, sôt még az utódját is - itt él, Antonio de Betancourtnak hívják. De nekem nem sikerült elhagynom ezt a helyet\na szkúnert zátonyok törték meg, a társam meghalt, és nekem a többi túlélô között sikerült ide eljutnom. A legrosszabb, hogy nem találtam meg, amit kerestem - sem Szent Anna kincstárát, sem aranyércet.";
			link.l1 = "Elolvastam Alvarado feljegyzéseit is. Érdekes történet.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "A rivadók átkozott pogány söpredék. Ôk a néger rabszolgák leszármazottai, akiket de Betancourt hozott ide Afrikából. Bár megtanultak a fehérektôl pengét és muskétát használni, de attól még vademberek\nNarwhalok jó emberek, okosak és tisztességes harcosok. Kiváló mesteremberek vannak közöttük. Sokukat ismerem. Talán egy nap én is csatlakozom a klánjukhoz\nA kalózok a pokolba is, a fenébe velük. Nem mi hívtuk ôket, de megérkeztek, elrabolták az ellátmányunkat, és el merték adni a saját élelmünket! Szemetek, mi? Kár, hogy nem tudjuk elûzni ôket, és együtt kell élnünk a jelenlétükkel.";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Persze. Az embernek pénzt kell keresnie. Az átkozott kalózok aranyat, pesót vagy más értéktárgyakat követelnek az ételért. Sokkal olcsóbban adják el az ilyen helyieknek, mint én, mint a klánoknak, de ez amúgy sem jótékonyság. Hála Istennek, a külsô gyûrûnél van elég hajó a fosztogatáshoz, sokukhoz még mindig nem nyúlt senki a hajótörésük óta\nEgy érdekes tevékenység, mégis veszélyes: beleeshetsz a vizes rakodótérbe, csontot törhetsz, beszorulhatsz a kötelekbe, szétzúzhatnak a fadarabok, vagy óriás rákokkal találkozhatsz - gyakran látogatják kint a raktereket.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sajnos, ez nem így van. Azt mondják, hogy a Kubából érkezô kalózok és csempészek már régen is megfordultak itt - ellátmányt cseréltek aranyra és árukra. Még narválok is meglátogatták a településeket. De ez már történelem. Senki sem kockáztatná meg, hogy törékeny és kis hajókon hajózzon. A viharok egy pillanat alatt elpusztítják a kis csónakokat, és itt nincsenek jobb hajóink.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "Basszus!";
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
