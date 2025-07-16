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

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Una historia triste, ¿verdad?";
				link.l1 = "¿Quién es usted?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Saludos, capitán.";
				link.l1 = "¡Un momento! ¡Ya nos hemos encontrado antes!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Uno. Dos. Tres.";
				link.l1 = "Terminemos este espectáculo. ¿Quién es usted?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "¿Sabe qué tiene de especial este panteón? Aquí descansan dos almas unidas... por la sangre. Padre e hijo de Alameda. Uno cayó a manos de los pecadores, el otro... encontró su camino hacia Dios.";
				link.l1 = "El diario de don Fernando me trajo hasta aquí.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "¿Ha visto a la señora Bishop? Un destino triste, ¿verdad? Pero, me temo, merecido.";
				link.l1 = "¿Conoce a Elizabeth?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grimm.";
				link.l1 = "¿Lo conocía, por supuesto?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nTres más. Cuando cuente seis, sabrá todo.";
			link.l1 = " Si no me da respuestas claras ahora mismo, yo...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nVa bien, capitán. Se ha ganado saber mi nombre. Me llamo Diego de Landa.";
			link.l1 = " ¿De verdad es usted sacerdote?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Ante todo, soy un artista. Pero no nos apresuremos...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... El diario. Una cosa sorprendente, la palabra escrita. Es como... un sendero en la oscuridad. Lleva a donde aguarda... una revelación. Nuestra parroquia solía recibir a don Fernando con frecuencia. Especialmente en su último año.";
			link.l1 = "¿Oficia usted en la parroquia local? ¿Conocía a don Fernando?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Yo... observaba su camino. Y ese libro que usted tomó. ¿Sabe qué tiene de especial?";
			link.l1 = "Parece antiguo.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "¿Antiguo? Oh no. Está... iluminado. La Biblia del viejo don de Alameda. Cada palabra en ella es como un faro en la oscuridad. Tómela. Ayude a los hermanos en Cristo y entonces, quizás... también lo guíe hacia algo... mayor.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие

		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Oh, sí. Pobre mujer. Su esposo... no es precisamente un buen hombre. Dicen que sus plantaciones son las más productivas de Barbados. Y también las más crueles. ¿Sabe cuántos esclavos mueren mensualmente? Hace poco mató a golpes a un verdadero médico de Inglaterra – un hombre de gran inteligencia y talento. Pero el destino de ella no es mucho mejor, créame.";
			link.l1 = "Parece estar bien informado.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "La gente viene a mí a confesarse, capitán. Escucho lo que temen contar incluso a sus seres queridos. Sus miedos, sus pecados... su dolor.";
			link.l1 = "¿Y no teme persecuciones? No es fácil para un sacerdote católico en territorios ingleses.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Mis temores no se comparan con lo que usted acaba de dejar tras la puerta de esta casa. Y ese librito que tomó de esa pobre mujer... Si el miedo tuviera forma, sería justamente esa.\n"+
			"Buen día, capitán.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tigre, Tigre, miedo ardiente\n"+
			"Ardes en los bosques nocturnos\n"+
			"¿De quién fue la mirada inmortal, amorosa, que te creó tan terrible?\n"+
			"Por supuesto que lo conocía, capitán. Pero, ¿lo conocía usted?";
			link.l1 = "Nunca he conocido a un hombre con un destino más trágico.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Lo conoció, pero aún no lo ha comprendido\n"+
			"Entonces, no conocía a Grim. Aunque sostiene su cráneo en las manos.";
			link.l1 = "¿Qué?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "No es cristiano tratar así a los difuntos. Tome, una pequeña instrucción post mortem. Es mi regalo para usted\n"+
			"Buen día, capitán.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;

		//<-- Мементо

		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;

		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Dígame... ¿Por qué? Fue peligroso y estúpido. ¿Cuál es su fuego, capitán? ¿Qué lo impulsa?";
				link.l1 = "Eso no es asunto suyo.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Segundo.";
				link.l1 = "La última vez habló en acertijos. ¿También lo hará ahora?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Espere, de Landa. No puedo simplemente dejar que se vaya así.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{

			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{

			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "No puedo entenderlo. A los demás, sí. Pero a usted... aún no.";
			link.l1 = "¿A los demás?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Uno, por ejemplo, busca justicia. Otro... estaba obsesionado con las oscuras aguas de la muerte. La gente se pierde tan fácilmente en sus deseos. ¿No es cierto?";
			link.l1 = "Es usted un sacerdote extraño, padre.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Creo que me voy.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Por supuesto. Su trabajo apenas comienza, capitán.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nAhora mismo, tengo ante mí un verdadero enigma. Ya ha reunido dos... reliquias. ¿Le gusta coleccionar cosas así? ¿Es usted coleccionista?";
			link.l1 = "¿Cómo lo sabe?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "¿Cazador de trofeos?";
			link.l1 = "Repito mi pregunta: ¿cómo lo sabe?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;

		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "¿Amante de las emociones fuertes?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Claro. Por supuesto. Bueno, capitán, no lo detendré.";
			link.l1 = "Espere, padre. Aún no ha respondido a mi pregunta.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, capitán. No puedo. A veces, las respuestas hieren más que cualquier ignorancia. Vaya en paz. Y cuide su colección... de trofeos. Podrían serle útiles en el viaje que le espera.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Vamos, capitán. ¿No siente curiosidad? ¿No se está divirtiendo? ¿Ya tiene suficientes trofeos?\n"+
			"Ahí está su fuego, capitán. Le interesa saber qué viene después. Le encantan los barcos bonitos y los objetos curiosos\n"+
			"No puede evitar recogerlos todos.\n"+
			"\n"+
			"Puede dispararme ahora mismo.";
			link.l1 = "¿Qué?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Adelante. Pero entonces no lo sabrá todo ni conseguirá el conjunto completo de trofeos. Los barcos, eso sí, los tendrá todos\n"+
			"Buen día, capitán.";
			link.l1 = "(Dejarlo ir)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Dispararle)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 