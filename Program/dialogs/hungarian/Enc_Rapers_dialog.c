void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Menj a saját utadon, "+ GetSexPhrase("haver","lass") +". A végén még megköszöni nekünk, tudod.",
											 "Tûnj el! Hadd szórakozzanak az urak!",
											 "Ehhez semmi közöd, "+ GetSexPhrase("idegen","lány") +". Mi csak egy kicsit szórakozni fogunk, és kész!");
				link.l1 = LinkRandPhrase("Ezt nem fogom megengedni!","Azonnal hagyj fel gonosz terveiddel!","Nem tûrök el semmilyen erôszakot!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Értem, elmegyek. Elnézést a zavarásért.","Nem merlek többé zavarni. Elnézést a zavarásért.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Menj a saját utadon, "+ GetSexPhrase("haver","lass") +". A végén még megköszöni nekünk, tudod.",
											 "Tûnj el! Hadd szórakozzanak az urak!",
											 "Ez nem tartozik rád, "+ GetSexPhrase("idegen","lány") +". Mi csak egy kicsit szórakozni fogunk, és ez minden!!!");
					link.l1 = LinkRandPhrase("Ezt nem fogom megengedni!","Azonnal hagyj fel gonosz terveiddel!","Nem tûrök el semmilyen erôszakot!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Megvan, elmegyek. Elnézést a zavarásért.","Nem merlek többé zavarni. Elnézést a zavarásért.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hé, "+ GetSexPhrase("idegen","fiatal hölgy") +", miért keresed a bajt? Ez a lány egy 'jól ismert', egyén, a településünkön. Már kifizettük ôt, de észrevette magát, és úgy döntött, hogy elmenekül a pénzünkkel.",
												   "Hé, "+ GetSexPhrase("haver","lány") +", menj a saját utadon, és ne avatkozz bele az ügyeinkbe. Megnyertük ezt a lányt egy kockajátékban, de egy kicsit túl gyors volt, ezért elszaladt, már egy órája üldözzük ebben a dzsungelben.");
					link.l1 = "Nem érdekel, nem hagyom, hogy bántsátok!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ó, értem! És én majdnem hittem neki! Micsoda szajha...","Ah, nos, ez már más kérdés. Nos, jó szórakozást, srácok!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Menj a saját utadon, "+ GetSexPhrase("jóember","ifjú hölgy") +". Majd kitalálunk valamit nélküled is.";
					link.l1 = "Nem tûrök semmilyen erôszakot!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hé, "+ GetSexPhrase("idegen","fiatal hölgy") +", miért keresed a bajt? Ez a lány egy 'jól ismert', egyén, a településünkön. Már kifizettük ôt, de észrevette magát, és úgy döntött, hogy elmenekül a pénzünkkel.",
												   "Hé, "+ GetSexPhrase("haver","lány") +", menj a saját utadon, és ne avatkozz bele az ügyeinkbe. Ezt a lányt megnyertük egy kockajátékban, de egy kicsit túl gyorsan elszaladt, már egy órája üldözzük.");
					link.l1 = "Nem érdekel - nem hagyom, hogy bántsátok!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ó, értem! És én majdnem hittem neki! Micsoda szajha...","Ah, nos, ez már más kérdés. Nos, jó szórakozást, srácok!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Nos, akkor biztosan a megfelelô idôt választottad a sétához...","Szóval úgy döntöttél, hogy hôs leszel?") +" Intézzéttek"+ GetSexPhrase("el","el") +", fiúk!","Te "+ GetSexPhrase("nyálkás","mocsok") +"! Az utunkba merészeltek állni?! Vágd"+ GetSexPhrase("meg","meg") +"!");
			link.l1 = "Láttam már fenyegetôbb embereket is!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Tudnod kell, hogy elég sokba került nekünk! És ha olyan nemes vagy, elviheted ôt " + sti(pchar.GenQuest.EncGirl.price) + " pezóért."+ GetSexPhrase(" jól fogod érezni magad vele, he-he...","") +"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Itt a pénzed. Magammal viszem.","Ne vigyorogj már a fogaiddal. Magammal viszem a lányt. Itt a pénzed.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Tehát a pénz az, amit akarsz? Mit szólnál a hideg acélhoz?",
									 "Ez most viccesnek kéne lennie, nézd meg a lányt, te bolond! Meg van rémülve!",
									 "Kinek akarod beadni magad, te degenerált!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Miért hiszel neki egyáltalán? Milyen erôszak? Elszökött otthonról, és a fônökünk küldött minket, hogy megkeressük.";
			link.l1 = RandPhraseSimple("Nos, ez már egy másik történet. Menj, üldözd a szökevényt.","Ó, értem. Nos, akkor üldözd csak tovább... nekem pedig dolgom van.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Meséld el ezeket a meséket az unokáidnak, ha elég sokáig élsz ahhoz, hogy legyenek unokáid!","Kit akarsz átverni, te szemétláda?!");
			link.l2.go = "Node_6";
			link.l3 = "Egyedül viszem haza, hogy elkerüljem a bajt. Kik a szülei?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Meg akarsz halni? Ez a te döntésed...";
			link.l1 = "Nézd ki beszél.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "egy bolt tulajdonosa.";
					pchar.GenQuest.EncGirl.FatherGen = "egy bolt tulajdonosának";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "A kikötôi hivatalban szolgál.";
					pchar.GenQuest.EncGirl.FatherGen = "aki a kikötôi hivatalban szolgál.";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "a börtön parancsnoka.";
					pchar.GenQuest.EncGirl.FatherGen = "egy börtön parancsnokának";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "a hajógyár tulajdonosa.";
					pchar.GenQuest.EncGirl.FatherGen = "egy hajógyár tulajdonosának";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Édesapja " + pchar.GenQuest.EncGirl.FatherNom + ", a településen " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ". De kérem, ne hagyjon cserben minket, mert vele nem lehet packázni, élve megnyúz minket...";
			link.l1 = "Ne aggódjatok. Majd én átadom neki.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "És így találkozunk újra. Hol van a társad? Ó, hát, igazából nincs rá szükségem, ha már itt vagy.";
			link.l1 = "Uraim, tényleg úgy gondolom, hogy önök már éppen elég pénzt kaptak ahhoz, hogy békén hagyják a lányt.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "Egy láb...";
				break;
				case 1:
					sTemp = "egy kar";
				break;
				case 2:
					sTemp = "egy fül";
				break;
				case 3:
					sTemp = "egy orr";
				break;
				case 4:
					sTemp = "egy szem";
				break;
			}
			dialog.text = "Mit ér a pénzed a " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_GEN) + "kincseihez képest ? " +
							"Annyira kapzsi volt, hogy nem akarta feleségül venni a saját lányát, mert el akarta kerülni a plusz kiadásokat...\nDe a mi részünk a ládájában van! "+ 
							GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM) +" elvesztette a beszállásnál " + sTemp +"! Szintén mi van helyette? " + 
							"Szánalmas maréknyi ezüstöt? " + GetName(pchar.GenQuest.EncGirl.PirateIdx , pchar.GenQuest.EncGirl.PirateName1, NAME_NOM) + " mindig az összes zsákmányt a rejtekhelyére vitte. De most már nem adjuk fel! Mutasd meg, hol vannak a ládái!";
			link.l1 = "Nos, én bizonyára nem jelentkeztem a kapitányotok kincseinek ôrzésére, de nem tudom megmutatni a helyet... Mert nem tudom, hol van ez a hely.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Hazudsz!!! Érzem az arany illatát, ami ebbôl a barlangból árad! Mutasd meg a helyet, ha nem akarsz meghalni!";
			link.l1 = "Látom, hogy a szavaim nem tudtak meggyôzni. Talán a pengém kifejezôbb lesz?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Te "+ GetSexPhrase("cur","mocsok") +"! El az utamból!";
			link.l1 = "Argh!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Hello, jó "+ GetSexPhrase("férfi","hölgy") +". Panaszaink vannak önnel kapcsolatban.";
			link.l1 = "Kinek a panasza? Attól a kurvától?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Vigyázz a nyelvedre, rendben? Nem engedem, hogy sértegesd a húgomat! Elôször molesztáltad ôt a dzsungelben, aztán idehoztad "+ GetSexPhrase("további illetlenségekért","és kiraboltál engem") +".";
			link.l1 = "Hé, haver, tényleg végig kell hallgatnom mindezt?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "Nem. Egy szerény összeg, mindössze " + sti(pchar.GenQuest.EncGirl.BerglarSum) + " pezó megmenti Önt a sok gondtól.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Nos, a nemes cselekedetek manapság bizonyára kicsit drágák. Rendben, fogd...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Azt hiszem, olcsóbb lenne egy lyukat ütni a hasadba, hogy ne állj a kijárat felé vezetô utamon.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "Nem. De a zsebeidet is kifordítod, különben leszúrlak!";
				link.l1 = "Rendben, vedd el, te gazember! De ezt nem fogod megúszni...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Azt hiszem, egyszerûbb lenne, ha lyukat vágnék a hasadba, hogy ne állj a kijárat felé vezetô utamba.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Nagyon jó. Jó, hogy megszabadultál tôle.";
			link.l1 = "Sok szerencsét.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Persze, hogy nem fogok, persze... Nos, viszlát neked, "+ GetSexPhrase("pajtás","lass") +"."+ GetSexPhrase(" És ne feledd, nem vagy olyan jóképû, hogy bármelyik lány beléd szeretett volna, amint meglátott. Ez lenne a tanulság számodra.","") +"";
			link.l1 = ""+ GetSexPhrase("Az biztos!...","Tûnj már el!") +"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Úgy nézel ki, mint "+ GetSexPhrase("ilyen nemes ember","ilyen jól nevelt hölgy") +", miért a csúnya beszéd?";
			link.l1 = "Ez áll nekem a legjobban...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Nos, te kérted! Csiklandozzuk h"+ GetSexPhrase("im","er") +" acéllal, fiúk?";
			Link.l1 = "Imádkozz, mielôtt meghalsz!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Szóval, szeretnél csatlakozni, vagy mi? "+ GetSexPhrase("Tûnj el, nem elég mindannyiunknak","Tûnj el, amíg lehet, egy lány is elég nekünk") +"!";
			Link.l1 = "Nos, akkor nem foglak zavarni.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Nem fogom hagyni, hogy erôszak történjen!";
			Link.l2.go = "Node_2";
		break;				
	}
}
