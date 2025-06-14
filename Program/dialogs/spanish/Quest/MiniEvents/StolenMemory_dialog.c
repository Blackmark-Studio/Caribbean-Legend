void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
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

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, dicen que Port-au-Prince pierde su encanto cuando usted no sonríe. Hoy, me temo, es uno de esos días. Disculpe mi franqueza, ¿pero algo le preocupa?";
			}
			else
			{
				link.l1 = "Mademoiselle, he oído hablar de su belleza y encanto, y debo decir que los rumores no le hacen justicia. También dicen que Port-au-Prince pierde su encanto cuando usted no sonríe. Hoy, por desgracia, parece ser uno de esos días. Dígame el nombre del sinvergüenza que se atrevió a arruinar su día, y le juro que lo retaré a duelo para devolver la sonrisa a su hermoso rostro.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ay, mademoiselle, usted es demasiado atenta... Lo admito, su preocupación me conmueve. Pero, por desgracia, la causa de mi inquietud no es algo que pueda disiparse con una charla ligera. No es culpa de nadie, sólo son circunstancias que, me temo, están fuera del alcance incluso de la persona más decidida.";
				link.l1 = "¿Circunstancias? Le aseguro, mademoiselle, que para "+GetFullName(pchar)+" no hay barrera infranqueable. Cuénteme lo que ha pasado, quizás pueda ayudarla.";
			}
			else
			{
				dialog.text = "Oh, monsieur, parece que usted es un verdadero maestro de las palabras bonitas. Debo decir que casi logró hacerme sonreír. Pero, por desgracia, un duelo no resolverá mi problema. Quien arruinó mi día no es un villano, sino simplemente circunstancias que ni siquiera un caballero tan valeroso como usted puede dominar.";
				link.l1 = "¿Circunstancias? Le aseguro, mademoiselle, que el capitán "+GetFullName(pchar)+" puede con cualquier circunstancia. Y si llegara a fallar, le juro que me comeré el sombrero del primer transeúnte que vea.";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Si realmente insiste, le contaré lo que ocurrió. Pero antes necesito su palabra de que esta conversación quedará entre nosotros.";
				link.l1 = "Tiene mi palabra de honor, mademoiselle. Todo lo que me cuente quedará entre nosotros, incluso si debo llevar ese secreto al fondo del mar.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", sin duda sabe cómo animar incluso a una dama profundamente disgustada. Pero le ruego, tenga piedad de los sombreros de los pobres transeúntes. Si realmente insiste, le diré lo que pasó. Sólo deme su palabra de que mis palabras permanecerán en secreto entre nosotros dos.";
				link.l1 = "Le doy mi palabra, mademoiselle, de que todo lo que me diga será guardado en secreto, incluso bajo pena de muerte.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Muy bien. Hace poco desapareció un collar de mi habitación... pero no es una simple joya. Fue un regalo de alguien que ocupa un lugar especial en mi corazón. Ahora siento que he perdido algo mucho más valioso que un simple objeto\nHe pensado mucho en quién pudo hacerlo y sólo llegué a una conclusión. Me temo que fue uno de mis sirvientes. Son los únicos que tienen acceso a mi habitación y que podrían estar interesados en robar el collar. Pero no puedo acusarlos abiertamente...";
			link.l1 = "Es un asunto delicado, si no desea que esto se haga público. Pero si voy a ayudarla, necesito saber qué le obliga a guardar el secreto. Necesito esa información para no traicionarla sin querer. Debo saber a quién o a qué debo temer.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "¿No puede? Pues bien, mademoiselle, sólo me queda desearle suerte. No me agradan los juegos secretos. Me parece que su problema puede resolverse fácilmente con ayuda de la guardia. Pero usted ha decidido complicar las cosas.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "¿No puede? Entonces le ruego que me disculpe, mademoiselle, pero soy completamente inútil en este caso. No me gustan los juegos de secretos, señora. Su problema es absurdamente simple: la guardia podría resolverlo fácilmente. Pero parece que ha preferido convertirlo en un misterio digno de la corte de Madrid.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "¿Así es como enfrenta los problemas, "+GetFullName(pchar)+"? ¿Le confían un secreto y simplemente se da la vuelta? Espero que encuentre tareas más acordes con su extraordinario talento – tal vez contar barriles de ron o discutir con los comerciantes del puerto. Pero al menos, guarde nuestra conversación en secreto, si aún le queda algo de honor. Adiós.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;

		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);

			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "Juli_5":
			dialog.text = "Tiene razón, "+GetAddress_Form(NPChar)+", necesita saber la verdad. Ese collar fue un regalo de una persona a la que mi tío –el gobernador de la parte francesa de esta isla– desaprueba profundamente. Me prohibió mencionar siquiera su nombre. Si descubre quién me lo dio, las consecuencias podrían ser devastadoras, no sólo para mí, sino también para...";
			link.l1 = "No continúe, señora. Ya sé lo suficiente. Le prometo que haré todo lo posible para recuperar el collar sin poner en peligro su secreto.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Gracias, "+GetSexPhrase("monsieur "+pchar.lastname+"",""+pchar.name+"")+". Su determinación y tacto me han conmovido. Estoy segura de que mi secreto está a salvo en sus manos. Que la suerte le acompañe en esta difícil empresa.";
			if (pchar.sex == "woman")
			{
				link.l1 = "La suerte favorece a quien actúa, mademoiselle. Encontraré su collar, puede estar segura.";
			}
			else
			{
				link.l1 = "La suerte favorece a los fuertes, mademoiselle. Tan pronto como encuentre el collar, volverá directamente a sus delicadas manos.";
			}
			link.l1.go = "Juli_7";
		break;
		
		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;
		
		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, capitán, es usted... ¿Lo ha encontrado? Por favor, dígame que el collar está en su poder.";
				link.l1 = "Sus preocupaciones han llegado a su fin, Julie. Tengo el collar y ahora es un placer devolvérselo, donde realmente pertenece – en sus delicadas manos.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, capitán, es usted... ¿Lo ha encontrado? Por favor, dígame que el collar está en su poder.";
				link.l1 = "Lamentablemente no, Julie. Pero no se preocupe, haré todo lo posible para recuperarlo.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;

		case "Starpom_1":
			dialog.text = "Buenos días, monsieur. ¿Qué lo trae a bordo de mi barco?";
			link.l1 = "Busco a Tristan Renier. Tengo una oferta lucrativa para él.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "Necesito hablar con Tristan Renier por un asunto personal.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "El capitán no está a bordo en este momento. Creo que podrá encontrarlo en algún lugar de la ciudad.";
			link.l1 = "¿Sabe exactamente a dónde fue?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "El capitán no está a bordo en este momento. Creo que podrá encontrarlo en algún lugar de la ciudad.";
			link.l1 = "¿Sabe exactamente a dónde fue?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Lo siento, "+GetAddress_Form(NPChar)+", pero el capitán no comparte sus planes conmigo. Sólo sé que desembarcó hace un rato.";
			link.l1 = "Aun así, gracias.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;
		
		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "¿Quién demonios es usted? ¿Y con qué derecho irrumpe en mi habitación sin invitación?";
				link.l1 = "Me llamo "+GetFullName(pchar)+". Y tengo un asunto que tratar con usted.";
			}
			else
			{
				dialog.text = "¿Quién es usted, señorita? No recuerdo haber invitado a nadie. Aunque, lo admito, algunas visitas inesperadas pueden resultar interesantes. ¿A qué debo el honor?";
				link.l1 = "Me llamo capitana "+GetFullName(pchar)+". Y he venido por un asunto serio.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;

		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "¿Un asunto? ¿Qué demonios quiere decir con eso?";
				link.l1 = "Es muy sencillo. Tiene un collar que estoy buscando.";
			}
			else
			{
				dialog.text = "¿Un asunto, dice? Qué curioso... ¿Y qué tipo de asunto podría traer a una dama tan encantadora directamente a mi habitación?";
				link.l1 = "Tranquilícese, monsieur empalagoso, necesito un collar. Y sé que usted lo tiene.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "¿Un collar? Sí, tengo uno. ¿Y qué? ¿Cree que voy a entregarlo así como así?";
			}
			else
			{
				dialog.text = "¿Un collar, eh? Hm... Sí, tengo uno. ¿Y qué? ¿Cómo piensa conseguirlo?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Estoy dispuest"+GetSexPhrase("o","a")+" a ofrecerle cinco mil pesos. Es suficiente para adquirir una joya igualmente digna. Este collar debe volver a quien lo valora con todo su corazón.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Créame, no tiene muchas opciones: o me lo da voluntariamente y me marcho, o lo tomaré de su cadáver. Usted decide.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "¿Cinco mil? Bueno, capitán, tómelo si es tan importante para usted.";
				link.l1 = "Gracias. Ha tomado la decisión correcta.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Prueba superada", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "¡No compré ese collar para regatear con alguien como usted! Es un regalo para mi esposa, y no tiene nada que hacer aquí. ¡Lárguese antes de que lo echemos!";
				link.l1 = "Si no quiere entregarlo por las buenas, lo tomaré por la fuerza.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Habilidad insuficiente (25)", SKILL_COMMERCE);
			}
		break;

		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "¡Argh... cachorro insolente...! ¿Crees que me asustarán tus tontas amenazas? ¡Ja! ¡No sabes con quién te has metido!";
				link.l1 = "No me importa quién seas. Solo entrega el collar y me iré. ¿O realmente estás dispuesto a morir por una joya que para ti no vale más que cualquier otra chuchería?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Prueba superada", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "¡Compré este collar para mi esposa, no para negociar con gente como tú! No tienes nada que hacer aquí. ¡Lárgate antes de que te echemos!";
				link.l1 = "Si no quieres entregarlo por las buenas, entonces lo tomaré por la fuerza.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Habilidad insuficiente (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "¡Maldito seas tú y este collar maldito! Tómalo. Tómalo y vete antes de que cambie de opinión.";
			link.l1 = "¡Una decisión sensata! Adiós.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", ¡me has devuelto la alegría! Has recuperado no solo el collar, sino también una parte de mi alma. Tu nobleza es digna de admiración, y prometo que todos sabrán de tu valentía.";
			link.l1 = "Por favor, señorita, lo hice no por reconocimiento, sino porque tu sonrisa es la única recompensa que realmente valoro.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Eres tan modesto, "+pchar.name+". Pero, por favor, acepta este cofre con doblones. Solo sabiendo que aceptaste mi regalo podré sentir que te he agradecido como mereces.";
			link.l1 = "Por favor, señorita, no insistas. Tu palabra de agradecimiento vale para mí más que cualquier cofre con doblones.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Si eso te tranquiliza, señorita, aceptaré tu regalo. Pero debes saber que lo hice no por la recompensa. Tu agradecimiento es mucho más valioso para mí que estos doblones.";
			link.l2.go = "Juli_24_chest";
		break;

		case "Juli_24_nobility":
			dialog.text = "Casi olvido preguntar, ¿sabes quién robó este collar?";
			link.l1 = "Solo sé una cosa, señorita: parece que una tal Giselle le llevó este collar al comerciante. Y, por lo visto, no es la última joya que planea vender.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Juli_24_chest":
			dialog.text = "Casi olvido preguntar, ¿sabes quién robó este collar?";
			link.l1 = "Solo sé una cosa, mademoiselle: parece que una tal Giselle llevó este collar al comerciante. Y por lo visto, no es la última joya que planea vender.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "¿Giselle? ¡Pero si es mi doncella! La sospechaba... pero no quería creerlo. Lo más terrible es que no puedo castigarla abiertamente. Podría revelar mi secreto, y no puedo permitirlo.";
			link.l1 = "¿Entonces qué va a hacer? ¿Dejarla impune y permitir que siga robándole?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Oh, no, por supuesto que no. Primero me aseguraré de que ya no esté cerca de mí. Luego pensaré en cómo castigarla de manera que parezca que el castigo no vino de mí.";
			link.l1 = "La inventiva femenina es un arma peligrosa, especialmente en manos de una dama tan refinada e inteligente. Estoy segur"+GetSexPhrase("o","a")+" de que su doncella ni siquiera sospecha que la partida ya está jugada, y no a su favor.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, capitán, claro que preferiría no recurrir a tales trucos, pero... a veces la astucia es el único camino correcto.";
			link.l1 = "Sin duda, Julie. Me entristece despedirme, pero el deber llama. ¿Quién, si no yo, cuidará de mis marineros?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Hasta la vista, "+pchar.name+". Por favor, visite nuestro puerto con más frecuencia. A nuestra ciudad le falta gente "+GetSexPhrase("tan noble y valiente como usted.","con un corazón tan noble y un espíritu tan decidido como el suyo.")+"";
			link.l1 = "Me halaga, mademoiselle. Prometo que no dejaré pasar la oportunidad de volver a visitar su hermosa ciudad. Hasta pronto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! ¡Qué encuentro tan inesperado! ¿Sigues conquistando los mares?";
						link.l1 = "Encantado"+GetSexPhrase("","a")+" de verla, mademoiselle. Conquisto lo que puedo, aunque el mar, como siempre, es terriblemente caprichoso. ¿Y vos, espero que disfrutáis de la tranquilidad?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "¡Ah, capitán "+pchar.lastname+"! ¡Qué alegría verle! ¿Espero que sus asuntos marchan bien?";
						link.l1 = "Encantado"+GetSexPhrase("","a")+" de verla, mademoiselle. Los asuntos, como siempre, requieren tiempo y esfuerzo, pero encuentros como este alegran cualquier día. ¿Y cómo transcurren los suyos?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitán "+pchar.lastname+", ¿otra vez aquí? ¿Acaso aún quedan personas en nuestro modesto pueblo que no haya traicionado por un puñado de monedas de oro?";
						link.l1 = "Mademoiselle, comprendo sus sentimientos, pero actué"+GetSexPhrase("","a")+" como creí necesario. A veces las decisiones correctas causan dolor, y lamento que le haya afectado.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Capitán "+pchar.lastname+", ¿otra vez usted? ¿Su codicia es tan grande que no puede dejar nuestro pueblo en paz y busca otra víctima?";
						link.l1 = "Mademoiselle, lamento que mis acciones le hayan causado tales sentimientos, pero actué"+GetSexPhrase("","a")+" como creí necesario.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Últimamente todo ha estado realmente tranquilo y pacífico, y nada perturba esta idílica calma. Visite nuestro puerto con más frecuencia, capitán. Estoy segura de que aquí, tanto en nuestra tienda como fuera de ella, encontrará todo lo que desee.";
			link.l1 = "Gracias, mademoiselle. Procuraré visitar más seguido. Estoy segur"+GetSexPhrase("","a")+" de que su ciudad me seguirá sorprendiendo gratamente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_33":	
			dialog.text = "Gracias a usted, capitán, mis días son mucho más tranquilos. Espero que vuelva a honrarnos con su presencia pronto.";
			link.l1 = "Por supuesto, mademoiselle. Su ciudad siempre deja las mejores impresiones. Hasta pronto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Capitán "+pchar.lastname+", nos encontramos de nuevo. Sorprendente, ¿verdad?";
					link.l1 = "El destino parece sonreírnos hoy, mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Capitán "+pchar.lastname+", parece que nuestros caminos se han cruzado otra vez hoy.";
					link.l1 = "Así parece, mademoiselle. Me alegra"+GetSexPhrase(""," verte")+" de nuevo.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Parece que nos encontramos con demasiada frecuencia, capitán. ¿O simplemente no puede mantenerse alejado de aquellos a quienes ya ha traicionado?";
					link.l1 = "Mademoiselle, nuestros encuentros son casuales, pero comprendo su indignación. Solo espero que con el tiempo pueda comprender mis motivos.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "¿Qué más quiere? Dudo que tenga tan mala suerte como para que este encuentro sea una coincidencia. ¿O ha venido a recordarme su bajeza?";
					link.l1 = "Mademoiselle, no tengo intención de importunarla ni de recordarle el pasado. Este encuentro, en verdad, fue fortuito.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;
		
		
		
		
		
		
		
		
	}
}