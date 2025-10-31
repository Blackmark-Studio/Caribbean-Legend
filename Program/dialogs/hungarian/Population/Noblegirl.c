//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Hm. Ön a "+NationNameGenitive(sti(pchar.nation))+"zászló alatt hajózik, kapitány. Nem kívánok beszélni a hazám ellenségével. Hmph!";
					link.l1 = "Ah, igen. Egy igazi hazafi...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Mit akarsz tôlem, "+GetAddress_Form(NPChar)+"? Egy közönséges matróznak nem illik egy nemes hölggyel beszélgetni, de én hallgatlak.", "Ó, és mit akar tôlem egy ilyen bátor kapitány?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Nem fogom sokáig rabolni az idejét, csak azt szeretném kérdezni...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Tudnom kell, mi folyik a kolónián.", "Információra van szükségem.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Az egész város izgatott - don Fernando de Alamida, a királyi felügyelô megérkezett. Tudja, sok mindent láttam már itt, de ez... Nem a gyász változtatja meg az embert, hanem az, ahogyan kezeli. Azt mondják, más ember lett az apja halála után. Most már nem találsz megvesztegethetetlenebb és... kíméletlenebb szolgáját a Koronának az egész szigetvilágban.", "Nézd csak meg a 'Holy Mercy'! Azt mondják, maga a király rendelte meg, hogy különleges tervek alapján épüljön. És vegyük észre - egyetlen karcolás sincs rajta. Mintha maga Szûz Mária védelmezné. Bár hallottam pletykákat... talán nem is a Szûzanya.", "Tudod, hányszor próbálták már megölni don Fernandót? Tizenkét támadás nyílt vízen - és ez csak az elmúlt évben! Nos, egy ilyen hûséges és képzett legénységgel, és az Úr oltalma alatt - túl fogja élni a tizenharmadikat is!"), LinkRandPhrase("Hallottad? Don Fernando de Alamida megérkezett városunkba, és azt mondják, most is valahol az utcán van. Szeretném a saját szememmel látni ôt...", "Bonyolult ember ez a don Fernando. Egyesek szerint ô a megmentô, aki megtisztítja a hazát a mocsoktól. Mások azt suttogják, hogy valami megtört benne az apja halála után, és hamarosan mindannyian sírni fogunk. De én azt mondom nektek: ne féljetek tôle. Féljetek azoktól, akik azzá tették, ami.", "Milyen jóképû ember ez a don Fernando! De tudod mi a furcsa? Olyan, mintha senkit sem venne észre. Csupa kötelesség és szolgálat. Hallottam, hogy volt egy lány... de miután találkozott valami pappal, teljesen elutasította a világi örömöket. Mintha fogadalmat tett volna."), RandPhraseSimple(RandPhraseSimple("Átkozott felügyelô! Amíg ô itt van - a város olyan, mintha halott lenne. Se kereskedelem, se szórakozás. Még a légzés is, úgy tûnik, csendesebbnek kell lennie. És tudod, mi a legijesztôbb? Minden kikötôben ugyanez a helyzet. Mint az óramû. Ô királyi felsége nem találhatta ki szándékosan ezt a kínzást mindannyiunk számára!", "Don Fernando ismét meglátogatta az árvaházat. Nagylelkûen adakozik, órákig imádkozik. Egy ilyen méltó embert példaként kellene állítani az átkozott sikkasztók elé!"), RandPhraseSimple("Ha! 'Szent' Fernando ismét bezáratta az összes bordélyházat. Sebaj, nemsokára elhajózik, és újra kinyitnak.", "Megérkezett az insp... felügyelô, ez az! Don Fernando de Almeyda, vagy hogy is hívják, Alamida! Annyira fontos, hogy maga a kormányzó is lábujjhegyen járkál körülötte. Azt mondják, belenéz a szemedbe, és rögtön meglátja minden bûnödet. Félelmetes!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Megismételjem magam? Nem akarom, hogy a "+NationNameAblative(sti(pchar.nation))+"barátjaként gyanúsítsanak ! Távozzon, vagy hívom az ôrséget! Ôk szívesen beszélgetnének veled.";
					link.l1 = "Rendben, rendben, nyugodjon meg. Elmegyek.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Mi? Már megint te? Keress valaki mást, akivel beszélhetsz. Egy csomó komondor járkál errefelé, ôk inkább a te eseted. Most mennem kell, ma este bankett lesz a kormányzó rezidenciáján, és a pompadúrom még nincs kész!", 
					"Nem, most már tényleg idegesítô vagy! Hát nem érted? Vagy csak lassú az agyad?", 
					"Uram, kezdem azt gyanítani, hogy ön nem csak egy idióta, hanem egy gazember és egy faragatlan alak. Figyelmeztetem, hogy felhívom a férjemet, ha nem hagyja abba a hülye kérdéseivel való zaklatást!",
					"Még egy szó, és szólok a parancsnoknak, hogy csináljon magával valamit!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Értem. Viszontlátásra.", 
					"Igen, igen, emlékszem, csak elfelejtettem megkérdezni...",
					"Félreértettél...", 
					"Nyugodjon meg, hölgyem, máris indulok...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Rendben, hallgassuk meg.","Ó, rendben. Mit akarsz?","Kérdések? Rendben, tengerész, hallgatlak.");
			link.l1 = LinkRandPhrase("Meg tudod mondani az utolsó pletykát errôl a városról?","Történt itt mostanában valami érdekes?","Van valami hír a Karib-tengerrôl, hölgyem?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Megôrültél?! Megijesztesz! Tedd el a fegyvered, vagy szólok a parancsnoknak, hogy akasszanak fel az erôdben!", "Megôrültél?! Megijesztesz! Tedd el a fegyvered, vagy szólok a parancsnoknak, hogy akasszanak fel az erôdben!");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Rendben.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
