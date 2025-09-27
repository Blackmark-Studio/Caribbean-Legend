// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Hogy merészeled itt mutatkozni?! Nem tudom, hogy bátor vagy, vagy hülye...", "Hogy engedhették ezek a lusta csontok, hogy egy ellenség betörjön a rezidenciámba? Ez számomra felfoghatatlan...", "Biztos, hogy az ôreim egy rézpénzt sem érnek, ha ilyen fattyak szaladgálnak itt..."), 
					LinkRandPhrase("Mit akarsz,"+ GetSexPhrase("gazember","büdös") +"?! A katonáim már a nyomodba eredtek, "+ GetSexPhrase(", mocskos kalóz","") +"!", "mocskos gyilkos, azonnal hagyd el a rezidenciámat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("patkány","ribanc") +"! Hamarosan felakasztanak az erôdünkben, és utána nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Ezek a katonák egy pezót sem érnek...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a pofád, " + GetWorkTypeOfMan(npchar, "") + ", vagy kitépem a mocskos nyelvedet!", "Javaslom, hogy ülj csendben, és talán, élve túléled..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Ellenség a bányában! Riadó!";
				link.l1 = "Aaah, ördög!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", senor. A "+GetFullName(npchar)+"vagyok, a Los-Teques bánya bányamérnöke. Mire van szüksége?","Hello, senor. Mit szeretne?","Hmm... akart tôlem valamit, senor? Hallgatom.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Új vagyok itt, és szeretnék többet megtudni errôl a bányáról...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "Van egy rakomány a rakományomban, ami talán érdekes lehet önnek. Rabszolgák a bányájába, hogy pontos legyek. Akar alkudozni?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Csak köszönni jöttem, és máris megyek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "A Los-Teques bánya aranyat termel a spanyol korona számára. Minden, amit kitermelünk, Spanyolországé. Nemcsak aranyat, hanem ezüströgöket és értékes drágaköveket is találunk itt. Itt nem adunk el aranyat, mindent, amit kitermelünk, megerôsített konvojjal szállítunk az Óvilágba\nDe két kivétel van az arany- és ezüströgökre vonatkozóan. Elôször is, a helyi boltunkban vásárolhattok belôlük némi mennyiséget egy szállásmestertôl. Néha a fizetés nem érkezik ide idôben, ezért ilyen esetekre itt kell tartanunk némi megtakarított érmét, ezért engedélyezett a helyi kereskedelem\nMásrészt folyamatosan munkaerôszükségletet tapasztalunk, ezért a nuggetseket rabszolgákra cseréljük. Ezért szóljatok hozzám, ha van mit felajánlanotok, üzletet kötünk\nA bánya viselkedési szabályai szerintem egyértelmûek: ne lopjatok, ne zavarjátok az elítélteket és ne zaklassátok a katonákat, különben nem fogtok örülni a következményeknek.";
			link.l1 = "Rendben, köszönöm!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Természetesen, senor! Hányan vannak?";
			link.l1 = "Van "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Senor, sajnos jelenleg nincs szükségünk több rabszolgára. De a helyzet bármikor változhat, úgyhogy nézzen vissza néhány hét múlva vagy máskor.";
				link.l1 = "Rendben, senor, értem. Most nincs rájuk szüksége, de egy idô után szükségük lehet rájuk.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Természetesen, senor! Hányan vannak?";
				link.l1 = "Van "+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Minden rabszolgáért hajlandó vagyok fizetni egy arany vagy két ezüst rudat. Melyiket választod?";
			link.l1 = "Az aranyat.";
			link.l1.go = "slaves_g";
			link.l2 = "Ezüst rudak.";
			link.l2.go = "slaves_s";
			link.l3 = "Sajnálom, senor, de meggondoltam magam. Majd máskor.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Rendben. Hány rabszolgát akarsz eladni nekem?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Rendben. Hány rabszolgát akarsz eladni nekem?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Senor, nincs idôm hülye viccekre. Ha viccelôdni van kedve, menjen a kocsmába!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Senor, azt hiszem, pihennie kell. Talán nagyon fáradt, vagy hôgutát kapott. Menjen a kocsmába, pihenje ki magát, aztán folytathatjuk az alkudozást.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Sajnos, senor, jelenleg nincs szükségünk annyi rabszolgára. A bánya jelenleg "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Ennyit akarsz eladni?";
				link.l1 = "Igen, természetesen!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... Azt hiszem, nem.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Remek. Kérem, rendeljétek el, hogy hozzátok ôket a város kapujához. Elküldöm értük az embereimet.";
			link.l1 = "Ne aggódjon, senor. A rabszolgáit idôben leszállítják Önnek. Azonnal kiadok minden vonatkozó parancsot.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Kitûnô. Kérem, rendelje el, hogy hozzák ôket a város kapujához. Elküldöm értük az embereimet.";
			link.l1 = "Ne aggódjon, senor. A rabszolgáit idôben leszállítják Önnek. Azonnal kiadok minden vonatkozó parancsot.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("A rabszolgák cseréje ingotokra befejezôdött.");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
