void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "¿Qué quiere?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;

		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Capitán, el día es nuestro. La vanguardia está terminando de limpiar la cubierta inferior. No hay prisioneros... ¡Ah! Veo que usted tampoco se anduvo con rodeos.";
			link.l1 = "Por alguna razón esperaba un discurso pomposo de su parte. Pero se lanzó al combate de inmediato.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "¿Puedo decir algo?";
			link.l1 = "Te lo permito.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "No, aquí hemos terminado.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "¿Por qué los atacamos? Ese bergantín no representaba ninguna amenaza, no transportaba mercancías. De Grim se decían muchas cosas, claro, pero solo los traficantes de esclavos le temían. Hoy hemos matado a mucha gente — y no está claro para qué.";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "¿Hablas en nombre de la tripulación?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;

		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "Y no es la primera vez...";
			link.l1 = "¿Hablas en nombre de la tripulación?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;

		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "No. Créame, si la tripulación tuviera ese tipo de dudas, significaría que no estoy haciendo bien mi trabajo, y usted ya sería un muerto viviente.\n"+
			"Afortunadamente para usted, la gente obtuvo una buena ganancia con esta sangrienta aventura. ¡Los bolsillos de cada marinero de este barco están repletos de doblones!\n"+
			"No había carga valiosa — solo baratijas indígenas y amuletos espantosos. Pero los hombres igual se enriquecieron. Parece que Grim les pagaba bien.\n"+
			"Espero que no reclame su parte de ese oro, capitán.";
			link.l1 = "No lo haré, Alonso. Gracias por mantenerme informado.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Sí lo haré. Asegúrate de que mi parte llegue a mi camarote.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Siempre estoy de su lado, capitán. Por cierto, ¿qué piensa hacer con el 'Memento'?";
			link.l1 = "Tomarlo como premio — ¿qué otra cosa?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Aún no lo he decidido"+GetSexPhrase("","a")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Siempre estoy de su lado, capitán. Por cierto, ¿qué piensa hacer con el 'Memento'?";
			link.l1 = "Tomarlo como premio — ¿qué otra cosa?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Aún no lo he decidido"+GetSexPhrase("","a")+".";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Mejor no lo haga. Está cubierto de símbolos indígenas extraños. Y se cuentan cosas malas — dicen que sobrevivió a una epidemia horrible, y que en sus cubiertas casi bailaban los muertos.\n"+
			"Del esqueleto en la popa ni hablo: mientras no haya un idiota que se atreva a robar su cráneo por valentía, nadie más que yo se atreverá a hacer guardia allí.";
			link.l1 = "Entendido, Alonso. Vuelve a tus tareas.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;

		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "¡A la orden, capitán!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Capitán, disculpe molestar a estas horas.";
			link.l1 = "Informe, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "¿Capitán? ¿Y qué hace aquí? ¿Ha estado durmiendo aquí?";
				link.l1 = "No importa.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "En mi camarote no me sentía... cómodo.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Las cosas no van bien. ¡La moral de la tripulación está por los suelos! Ya hablan abiertamente de que el barco está maldito. Dicen que ven cosas por la noche.";
			link.l1 = "¿Qué cosas ven?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Pesadillas, la mayoría. Pero lo peor es que uno de nuestros hombres murió de fiebre. Un joven fornido, y se desplomó en unas horas.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "Eso lo decide el médico. "+sld.name+" sabe lo que hace.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "Eso no puede ser. Mantén a la tripulación bajo control, Alonso. Esa es tu responsabilidad.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "¡Entendido!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Entiendo. Muchos de la tripulación ahora duermen juntos — tienen miedo de quedarse solos. Como si uno pudiera estar solo en este barco...";
			link.l1 = "Como ves, yo tampoco lo logré. ¿Qué ha pasado?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Una pelea — José apuñaló a Marcel. Gritaba que 'llevaba la peste'.";
			link.l1 = "¿La situación ha empeorado?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = sld.name+" ya le informó esta mañana. Hemos perdido once almas. ¿Qué hacemos?";
			}
			else
			{
				dialog.text = "Otras once almas perdidas. ¿Qué hacemos?";
			}
			link.l1 = "Tomaré una decisión.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "Eso espero, capitán. ¿Qué hacemos con José? Matar no es cosa menor.";
			link.l1 = "A la horca tras el cambio de guardia. Demostraremos que controlamos la situación.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Treinta latigazos. Si sobrevive — será que Dios lo quiso.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "¡Entendido!";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "¡Entendido!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "¡Capitán! ¡Alarma! ¡Debe ir al entrepuente inmediatamente!";
			link.l1 = "¿Qué ha pasado?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;

		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Será mejor que lo vea usted mismo. ¡Vamos, deprisa!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;

		// Ya por la mañana
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "¡Buenos días, capitán!";
			link.l1 = "¿Eh?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;

		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Ehm, no tiene buena cara. ¿Mala noche? Bueno, le alegraré: la epidemia ha terminado. De hecho, resultó que nunca existió.";
			link.l1 = "¿Cómo es eso?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;

		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "La tripulación se asustó, creyó rumores tontos sobre un barco maldito. El poder de la autosugestión es terrible, se lo aseguro. Ha hundido más de un barco.";
			link.l1 = "¡Pero la gente murió!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;

		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Batallas, heridas sucias, carne salada podrida — la aritmética marina habitual. Si no nos hubiéramos alterado tanto con cuentos de barcos malditos, tal vez habríamos perdido a menos hombres.\n"+
			"El esqueleto en la popa tampoco ayudaba. Menos mal que un... bromista le robó el sombrero por la noche.\n"+
			"Y como el rayo no alcanzó el barco por tal sacrilegio, la tripulación se animó un poco y su astucia empezó a maquinar planes para molestar al esqueleto. Por ejemplo…";
			link.l1 = "¡No toquen al esqueleto!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;

		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Eh... Bueno, si le tiene cariño, por supuesto que no lo tocaremos. Que tenga buen día, capitán.\n"+
			"Por cierto, ¡excelente sombrero! Le queda muy bien. Al anterior dueño le quedaba pequeño.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Saludos, capitán. Debería hablar con el capitán Grim.";
				link.l1 = "Disculpa, marinero, pero destacas entre los demás.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "¿Algo más, capitán?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_1_1":
			dialog.text = "Entiendo lo que quiere decir, capitán. Serví con un capitán libre — como usted. Buscaba tesoros, comerciaba, tomaba encargos. Luego decidió asaltar unos comerciantes... y salió mal. Los sobrevivientes fueron ahorcados por piratería.";
			link.l1 = "¿Y el capitán Grim lo compró?";
			link.l1.go = "Memento_Sailor_1_2";
		break;

		case "Memento_Sailor_1_2":
			dialog.text = "Como un lote, como mercancía. Un marinero con experiencia siempre es útil, y el capitán Grim no recluta en las tabernas... Pero alimenta bien y paga generosamente. Y nosotros servimos — y participamos en el sorteo.";
			link.l1 = "¿El sorteo?";
			link.l1.go = "Memento_Sailor_1_3";
		break;

		case "Memento_Sailor_1_3":
			dialog.text = "Perdón, no deberíamos hablar de eso.";
			link.l1 = "¿Por qué no se va?";
			link.l1.go = "Memento_Sailor_1_4";
		break;

		case "Memento_Sailor_1_4":
			dialog.text = "¿A dónde ir? Al menos aquí hay una oportunidad. Tal vez tengamos suerte. Cada barco tiene su propio sorteo. El capitán Grim tiene el suyo, usted el suyo. No somos personas, sólo números en los libros del barco.";
			link.l1 = "En mi barco las reglas son distintas.";
			link.l1.go = "Memento_Sailor_1_5";
		break;

		case "Memento_Sailor_1_5":
			dialog.text = "Como diga, capitán. Que tenga un buen día.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;

		case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "¡Hacía tiempo que no teníamos visitantes en nuestro glorioso barco!";
				link.l1 = "¿Eres marinero? No lo pareces.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "¿Algo más, capitán?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_2_1":
			dialog.text = "¡Ja! El capitán me compró directamente de la celda. Me iban a colgar en Port Royal: maté a un tipo — un jovencito que se la pasaba recitando versos. Lo merecía, el bastardo.";
			link.l1 = "¿Así que tuviste suerte?";
			link.l1.go = "Memento_Sailor_2_2";
		break;

		case "Memento_Sailor_2_2":
			dialog.text = "¡Y tanto! El capitán no escatima, aunque a veces hay que participar en sus... juegos.";
			link.l1 = "¿Qué juegos?";
			link.l1.go = "Memento_Sailor_2_3";
		break;

		case "Memento_Sailor_2_3":
			dialog.text = "Cada semana sacamos palitos: el corto — te toca un trabajo muy peligroso o incluso saltar por la borda. Divertido, vaya. No para todos, claro, pero el capitán dice que así se filtra a los indignos.";
			link.l1 = "¿Indignos de qué?";
			link.l1.go = "Memento_Sailor_2_4";
		break;

		case "Memento_Sailor_2_4":
			dialog.text = "¿Y yo qué sé? El capitán suelta discursos como un cura: '¡Solo al conocer la muerte se puede vivir de verdad!'\n"+
		"(escupe)";
			link.l1 = "Escupir en la cubierta se castiga con latigazos. Te comportas como un bandido, no como un marinero. Adiós.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Buenos días, capitán.";
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "¿Algo más, capitán?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_3_1":
			dialog.text = "El capitán Grim capturó el barco negrero en el que viajaba. Estaba enfermo, muriéndome en la bodega... no recuerdo mucho. Me desperté ya aquí, en el 'Memento'.";
			link.l1 = "¿Y qué pasó con los otros esclavos?";
			link.l1.go = "Memento_Sailor_3_2";
		break;
		
		case "Memento_Sailor_3_2":
			dialog.text = "No lo sé. El capitán dice que liberó a todos, pero yo fui el único que trajeron al barco. Los demás probablemente huyeron a las islas o murieron por las heridas. Recuerdo poco de ese día.";
			link.l1 = "Pero estás libre.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "¿Libre? Aquí nadie es libre. El capitán da oro, comida, ropa, pero exige lealtad total — y organiza esa maldita rifa.";
			link.l1 = "¿Rifa?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Cada semana alguien saca el palillo corto y recibe un trabajo peligroso del que no todos regresan. El capitán dice que así se separan los vivos de los muertos.";
			link.l1 = "¿Y lo toleran?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Cada uno espera tener suerte. El capitán tiene una llave para cada uno: miedo a la horca, codicia por el oro, deuda por una vida salvada. A mí nada de eso me interesa. No necesito dinero, y una deuda… ¿qué deuda si no recuerdo nada?";
			link.l1 = "¿No temes hablar de esto abiertamente?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "¿Y qué pueden hacerme? Este es un barco de muertos, capitán, y yo estoy en mi lugar. Pero usted — no.";
			link.l1 = "Como digas. Adiós.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bienvenido a bordo del 'Memento', capitán.";
				link.l1 = "¿Un soldado español en un barco pirata? Eso no es común.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "¿Algo más, capitán?";
				link.l1 = "Nada.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		case "Memento_Sailor_4_1":
			dialog.text = "Soy un desertor. El capitán Grim me compró directamente del patíbulo en la plaza de San José. Pagó caro — ¡un saco entero de doblones por mi pellejo polvoriento!";
			link.l1 = "¿Y por qué lo sentenciaron?";
			link.l1.go = "Memento_Sailor_4_2";
		break;
		
		case "Memento_Sailor_4_2":
			dialog.text = "El oficial Saldo nos envió a custodiar obreros en la selva, donde la mitad muere de fiebre en una semana. Decidí que mi vida vale más. Ahora sirvo a quien supo valorarla con buen oro.";
			link.l1 = "¿No se arrepiente?";
			link.l1.go = "Memento_Sailor_4_3";
		break;

		case "Memento_Sailor_4_3":
			dialog.text = "Por mucho que se alargue la cuerda... El capitán es generoso con quienes le son leales. Claro, a veces organiza extrañas pruebas — el sorteo. No todos tienen suerte.";
			link.l1 = "¿Sorteo?";
			link.l1.go = "Memento_Sailor_4_4";
		break;

		case "Memento_Sailor_4_4":
			dialog.text = "Ya sabe. A algunos les toca trabajar en lo alto del mástil en plena tormenta, a otros — ir al frente. El capitán dice que así se prueba si uno está preparado. No sé para qué, pero espero tener suerte.";
			link.l1 = "Buena suerte... supongo.";
			link.l1.go = "Memento_Sailor_4_5";
		break;

		case "Memento_Sailor_4_5":
			dialog.text = "Gracias, capitán. La muerte nos sigue a todos de todas formas.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bienvenido a bordo del 'Memento', colega. Me llamo Mortimer Grim.";
				link.l1 = "Capitán "+GetFullName(pchar)+". Gracias por recibirme...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "¿De qué más hablaremos?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Tiene una espada impresionante, capitán.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Su catalejo combina muy bien con el esqueleto.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Debo decir que su tripulación es bastante variada.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Nada más... colega. Buen viento.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;

		case "Memento_MortimerGrim_2":
			dialog.text = "El Caribe es generoso con los que corren hacia el cadalso, lo sé bien.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;

		case "Memento_MortimerGrim_3":
			dialog.text = "¿Sí? ¿Querías preguntarme algo?";
			link.l1 = "Tiene un esqueleto colgado detrás de usted.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Buen viento hoy, ¿verdad? Y el clima excelente.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;
		
		case "Memento_MortimerGrim_4":
			dialog.text = "¿Qué esqueleto? Detrás de mí solo está el azul mar Caribe.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_5":
			dialog.text = "De acuerdo, colega. ¡Ojalá todos los días fueran así!";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;

		case "Memento_MortimerGrim_6":
			dialog.text = "¡Ja, ja, ja! ¡Ese chiste nunca envejece! No se asuste: el viejo Yorick, igual que este barco, es un recuerdo de mi vida pasada. Literalmente, por supuesto.";
			link.l1 = "¿Literalmente?";
			link.l1.go = "Memento_MortimerGrim_7";
		break;

		case "Memento_MortimerGrim_7":
			dialog.text = "Colega, ¿tiene miedo a la muerte? No es una amenaza, realmente tengo curiosidad.";
			link.l1 = "Por supuesto. Quien diga lo contrario, miente.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "No. Todos acabaremos allí.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "¿Y usted?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;

		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "¡Oh! La muerte es la madre de todos los miedos. Soledad, oscuridad o castigo: todas son solo máscaras suyas.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "¡Oh! La muerte es la madre de todos los miedos. Soledad, oscuridad o castigo: todas son solo máscaras suyas.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "¡Oh! La muerte es la madre de todos los miedos. Soledad, oscuridad o castigo: todas son solo máscaras suyas.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Memento_MortimerGrim_9":
			dialog.text = "¿Por qué ir tan lejos? Mire al viejo Yorick: un montón de huesos con una linterna entre las costillas — ¡y hasta a un capitán tan temible como usted lo hizo temblar!";
			if (startHeroType == 4)
			{
				dialog.text = "¿Por qué ir tan lejos? Mire al viejo Yorick: un montón de huesos con una linterna entre las costillas — ¡y hasta a la valiente Hélène, hija del gran Sean MacArthur, la puso nerviosa!";
			}
			link.l1 = "Habla bonito, pero no dijo qué hacer con todo eso.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;
		
		case "Memento_MortimerGrim_10":
			dialog.text = "Yo lo sé, pero no todos aceptan mi medicina. Siempre se puede probar más tarde, pero primero dígame: ¿qué piensa usted?";
			link.l1 = "La Biblia dice que la muerte no existe.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Si empiezo a temer, el barco está perdido.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "La respuesta se ahogó en el fondo de una botella de ron.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;

		case "Memento_MortimerGrim_11_1":
			dialog.text = "Es cierto. Lo único con lo que estoy de acuerdo en ese libro.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_2":
			dialog.text = "Loable. Pero no se preocupe: la muerte no existe.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_11_3":
			dialog.text = "¡Yo-ho-ho! Un cínico. Pero incluso sin ron le digo: la muerte no existe.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "Es simple: la verdadera vida comienza solo cuando uno vence a la muerte. Yo estuve allí, más allá del velo, y créame, solo ahora empecé a vivir de verdad.";
			link.l1 = "¿Disculpe?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "No importa, colega.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "¡Me alegra que lo haya notado, colega! No soy un fanfarrón, pero ¿qué clase de pirata sería sin un aterrador cutlass?";
			link.l1 = "¿Eso es tan importante?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;

		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "¡Y tanto! La única vez que aligeré el tesoro del barco por razones personales fue precisamente para esta espada. ¡Dos mil doblones de oro, colega! Diablo, si pudiera resucitar por segunda vez, lo haría solo por su precio.\n"+
			"El arma, eso sí, es excelente. Pero, como si le faltara algo...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Un regalo de cierta persona. Un excelente conversador, que comprendía la muerte como nadie — y con una gran imaginación, como habrá notado.";
			link.l1 = "Se ve espeluznante.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, colega.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Mi tripulación tiene mucho más en común entre ellos que, por ejemplo, la suya... Todos fueron liberados por mí del lazo o de las cadenas, cada uno ha sentido el aliento de la muerte. Ese sentimiento une a las personas más que la sangre o una bandera.";
			link.l1 = "Entonces, ¿no recluta en las tabernas?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Se sorprendería de lo dispuestos que están los antiguos esclavos y condenados a unirse a la tripulación: ¿cambiar la bodega de un negrero o el cadalso por la cubierta del 'Memento'? Ahora tengo 178 hombres en el barco — y todos me lo deben.";
			link.l1 = "Pero tiene que pagarles y mantener el barco. La gratitud sola no basta.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Soy un pirata exitoso, colega. Un verdadero hostis humanitatis. Así me llamarían los verdaderos enemigos de la humanidad — los traficantes de esclavos y las cabezas coronadas. La única diferencia entre ellos es el nombre.\n"+
			"Por suerte, tienen mucho oro. Las monedas de los cofres de los comerciantes de almas las uso para salvar a quienes la corona ha condenado a morir. El resto lo reparto entre la tripulación — y yo no necesito nada. ¿Para qué quiere oro un muerto? Pronto lo entenderán...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "Así están las cosas de jodidas, capitán.";
			link.l1 = "¿Qué demonios es esto?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Usted fue el único que quedó. La enfermedad se llevó a todos. Nos falló.";
			link.l1 = "¡Eso no puede ser!";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Nos trajo a un barco maldito.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "¡Condenó a todos a la muerte!";
			link.l1 = "¡¿Alonso, qué te pasa?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;

		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "¿Qué pasa, colega? ¿Te echaste atrás? Entonces, ¿para qué atacaste?";
			link.l1 = "¿Grim? ¡Pero estás muerto!";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "¡Ja! Lo que está muerto no puede morir. Y además, te estás adelantando: tal vez ganaste el abordaje, pero... ¿sobrevivirás? ¡Eso lo veremos ahora!";
			link.l1 = "¡Esa batalla fue hace semanas! ¡Estás muerto!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Ahora sí... Felicitaciones por la victoria.";
			link.l1 = "¿Grim?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Sabes, me alegro. Sinceramente me alegra que me hayas matado. De verdad.";
			link.l1 = "¿De qué estás hablando?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Soy un cobarde, colega. Un cobarde miserable que temía a la muerte, como tantos otros. Cuando mi tripulación murió de peste... y por mi culpa, enloquecí de miedo. Estuve un mes a la deriva en un barco de muertos.";
			link.l1 = "¿Qué pasó en realidad?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "No pasé la prueba de la muerte. En vez de aceptarla, sobrevivir y aprender algo, solo me dio más miedo. Y para acallar ese miedo... hice que otros pasaran por lo mismo que yo.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;

		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Gracias, colega. Por liberarme de esta... existencia. Ahora sé con certeza que la muerte no existe. Y ya no tengo miedo. No queda a quién culpar ni a quién someter.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "No separes al 'Memento' de su capitán. Mortimer... el capitán Mortimer fue un buen hombre. Búscalo en Dominica. Y el barco... el barco te aceptará.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, colega. Los muertos enseñan a los vivos. Adiós.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 