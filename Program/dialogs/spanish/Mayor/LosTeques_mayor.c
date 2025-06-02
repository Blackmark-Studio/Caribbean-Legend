void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("¿Te atreves a venir aquí? Acción audaz...","¡¿Cómo esos imbéciles han dejado que un enemigo invada?! No lo entiendo...","Bueno, mis guardias son inútiles si algún idiota anda por mi residencia..."),LinkRandPhrase("¿Qué quieres, bastardo? ¡Mis soldados ya te han encontrado y no te escaparás"+GetSexPhrase(", sucio pirata","asquerosa pirata")+"!","¡Sucio asesino, aléjate de mi residencia! ¡Guardias!","¡No te tengo miedo, bastardo! Serás ahorcado, no te saldrás con la tuya..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Los soldados no cuestan nada...","Jamás me atraparán."),RandPhraseSimple("Cierra la boca, "+GetWorkTypeOfMan(npchar,"")+", o te cortaré la lengua y te la meteré en la garganta...","Te diría, camarada: siéntate en silencio, y puede que veas otro día..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "¡Enemigo en mi residencia! ¡Alarma!!!";
				link.l1 = "¡Mierda!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" señor. Yo soy "+GetFullName(npchar)+", comandante de la mina de Lost-Tekes que pertenece a "+NationKingsName(npchar)+". Ahora, ¿sería tan amable de decirme el propósito de su visita, "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Es mi primera vez aquí y quiero saber más sobre este asentamiento y sus leyes...";
				link.l1.go = "info";
				link.l2 = "Solo quería saludarte, ya me voy.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "¿Usted otra vez, Señor? ¿Qué más quiere?";
			link.l1 = "No es nada. Me voy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Respeto tal disciplina. Bueno, te pondré al tanto en ese caso, ya que estás tan interesado.\nLa mina de Los-Teques es propiedad de la Corona Española. Aquí extraemos mineral crudo de plata y oro, así como pepitas de plata y oro. Todo el oro y la plata pertenecen a España y son transportados al Viejo Mundo.\nLa mina está bien custodiada, una unidad de soldados de élite españoles está siempre estacionada aquí. Los piratas han hecho varios intentos de robar nuestra mina, pero las consecuencias siempre fueron malas... para ellos.\nComo puedes ver, es un pueblo pequeño. Tenemos una taberna y una tienda. Puedes comprar lingotes de oro y plata a buen precio allí. Además, nuestro intendente, que también es comerciante en la tienda, puede venderte otros metales y minerales interesantes.\nLa mayoría de nuestros trabajadores son convictos, pero también tenemos una pequeña cantidad de esclavos negros. Como puedes ver, siempre necesitamos nueva mano de obra, cada día al menos uno de estos condenados convictos muere.\nAsí que, si nos traes esclavos, los intercambiaremos por pepitas. Contacta a nuestro ingeniero jefe para tales asuntos. Puedes encontrarlo en la galería.\nCompórtate aquí. No inicies duelos o peleas, no intentes robar nada, especialmente oro o plata. No tenemos una prisión aquí, pero tenemos un consejo de guerra.\nEso es prácticamente todo. Sigue estas simples reglas y no tendrás problemas. Se te permite moverte libremente dentro de la mina. No olvides visitar la taberna, ellos realizan ciertos... servicios con mi permiso. ¡Bienvenido!";
			link.l1 = "¡Mis gracias!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "¡Robo!!! Eso es inaceptable! Prepárate, "+GetSexPhrase("camarada","chica")+"...";
			link.l1 = LinkRandPhrase("¡Mierda!","¡Caramba!!","¡Maldita sea!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
