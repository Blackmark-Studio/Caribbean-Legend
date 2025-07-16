// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos los rumores de "+GetCityName(npchar.city)+" a su servicio. ¿Qué le gustaría saber?","Justo estábamos hablando de eso. Debes haberlo olvidado...","Esta es la tercera vez hoy que hablas de alguna pregunta...","Repetís todo como un loro...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabes, "+NPChar.name+", tal vez la próxima vez.","Correcto, lo he olvidado por alguna razón...","Sí, realmente es la tercera vez...","Sí...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "He oído que hubo un gran lío en la isla... ¿Esclavos?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "¡He oído que ese miserable canalla Bart el Portugués finalmente ha encontrado justicia! ¿Está en prisión? ¿Sabes cuándo será su ejecución? Quiero venir a verlo, tengo una cuenta pendiente con esa escoria...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Oye, "+npchar.name+", escuché que recientemente contrataste a una nueva y hermosa camarera... ¿y ya ha desaparecido?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Oye, "+npchar.name+", la noche de la desaparición de Betsy, ¿no notaste a alguien sospechoso cerca de ella? ¿Tal vez hablaba con alguien?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{
				link.l1 = "Bueno, "+npchar.name+", buenas noticias: tu preciada camarera está viva y bien. Tendrás que volver a aumentar tus reservas de ron, pronto regresará la clientela.";
				link.l1.go = "TBP_Tavern3_21";
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Ay, nunca ha habido tal desorden... Más de mil negros se han rebelado. Dos plantaciones han sido reducidas a cenizas y cada uno de sus amos fue asesinado. El comandante está preocupado de que los esclavos vayan a atacar la ciudad, así que ha impuesto la ley marcial. Y todo comenzó por dos negros, un macho llamado Tamango y una hembra llamada Isauri...";
			link.l1 = "Parece bastante dramático. Cuéntame toda la historia, ¿quiénes son esos negros?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango e Izaura, esclavos en la plantación de Blenheim, la primera plantación quemada. Estos dos negros se amaban. Pero un hijo del plantador, Leonsio, llegó de Europa y se encaprichó con la mulata. Quería convertir a Izaura en su concubina personal. Al negro Tamango no le gustaba la idea y a Izaura tampoco, ella realmente amaba al diablo negro.\nEse Tamango era una especie de jefe o algo así en África... Un negro gigante, más negro que el pecado y mortal con un hacha, los otros negros le temían y respetaban. Así que este negro lidera a los otros esclavos en un levantamiento. Atacaron a los guardias por la noche, mataron a todos los blancos fuera de la gran casa, a los mulatos también.\nEntonces Izaura abrió las puertas de la plantación y los simios salvajes asesinaron a todos dentro. Blenburg fue reducido a cenizas. Luego los esclavos huyeron a las selvas y desaparecieron...";
			link.l1 = "Bueno, ¡qué historia, suena como la trama de una novela! Una verdadera revuelta de esclavos, como en la Antigua Roma. ¿Cómo te enteraste de todo eso, por cierto?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "Rumores, mynheer, la tierra está llena de ellos. El ron suelta lenguas, todo lo que tienes que hacer es escuchar...";
			link.l1 = "¿Y cómo terminó todo eso? ¿Han encontrado a esos negros?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "¡Ja, ni lo sueñes! Hasta que los refuerzos finalmente lograron llegar, nadie puso un pie en la jungla. Luego llegó un barco de guerra de la Compañía con una unidad de soldados y registraron la isla. No encontraron ni piel negra ni cabello rizado de un solo negro suelto.";
			link.l1 = "¡Vaya, cómo lo ves! ¿Mil negros desaparecieron en el aire como por arte de magia?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "En realidad al agua.";
			link.l1 = "¿De qué estás hablando, "+npchar.name+". ¿Sabes tan bien como yo que los negros no pueden nadar?";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... oh no, esos negros no son cebo de tiburón tan fácilmente. La cosa es que la noche siguiente al motín, un bergantín desapareció de los muelles. ¡Puedes pintarme de negro y tocaré el banjo y bailaré para ti si no fue obra de ese bribón Tamango y sus negros! Por eso ya no están en la isla.";
			link.l1 = "Ja, ahora lo he oído todo, "+npchar.name+". ¿Esperas que crea que un grupo de negros medio salvajes pueden manejar velas y navegar? Antes esperaría que un barco de monos llegara a toda velocidad desde Guinea.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Yo tampoco lo creía, mynheer, pero la prueba está en el barco desaparecido. Tal vez uno de esos negros solía servir como mayordomo en un barco y aprendió alguna técnica de navegación. ¡Quizás usaron magia negra, quién sabe! Pasa a visitarme de nuevo, "+pchar.name+", la próxima vez conseguiré más historias para ti.";
			link.l1 = "¡Gracias! Bueno, es hora de que me ponga en marcha.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Sí, eso es correcto. Atraparon a ese pirata. ¿Y puedes creer cómo? Lo recogieron en un bote pequeño solo en medio del mar. Ni siquiera hizo un ruido antes de ser enviado a la bodega para los ratones. Es realmente divertido, ¿sabes?, ¡un pirata tan peligroso fue atrapado como un novato!";
			link.l1 = "¿Y por qué estaba él solo en el mar?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Probablemente decidió separarse de sus compinches, sin duda... No pudieron dividir el botín de manera justa. Ahora está en manos de la Compañía misma, y esos tipos no se toman bien las bromas. Dicen que se apoderó de uno de los barcos de la Compañía con algo valioso. Aparentemente, es solo porque quieren sacarle algo de información, todavía no está colgando de una soga.";
			link.l1 = "Entonces, ¿sabes cuándo será su ejecución?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Nadie lo sabe. Creo que una vez que la Compañía descubra lo que quiere, le atarán un lazo de cáñamo alrededor del cuello. El portugués está en la prisión ahora mismo bajo guardia confiable. Recientemente trajeron aquí a su contramaestre también. Su historia fue aún más sorprendente, se entregó a los holandeses en Philipsburg. Así que lo han puesto en una celda justo al lado de su excapitán, ahora son vecinos, je-je...";
			link.l1 = "¡Suceden milagros! Muy bien, estaré atento a las noticias. No quiero perderme esa ejecución. ¡Adiós, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "¡Oh, si la hubieras visto, capitán! ¡Betsy... qué gracia, qué sonrisa! Los hombres venían en masa solo para mirarla. Y cuánto dinero dejaban en mi taberna... Pero hace tres días que no se presenta a trabajar. Por supuesto, envié gente a su casa, pero no está. La casa está revuelta y sus pertenencias personales han desaparecido\nYa no sé qué pensar. La guardia, como siempre, se desentendió. Dicen que tienen cosas más importantes que hacer que buscar a muchachas desaparecidas, que seguro solo se fue de parranda y pronto volverá. Capitán, ¿podría buscarla? Si la trae de vuelta, le pagaré cien doblones. No puedo perderla así como así, ¿entiende? ¡Es un verdadero hallazgo! ¡Tengo que recuperarla cueste lo que cueste!";
			link.l1 = "Veré qué puedo hacer. ¿Se comportó de forma extraña antes de desaparecer, o recibió alguna mala noticia?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "¿Buscar a una chica que seguramente simplemente se escapó? Tengo cosas más importantes que hacer. Arréglatelas solo.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "El último día antes de desaparecer se fue contenta, ¡incluso feliz! Ni rastro de preocupación, ni una palabra de que planeaba irse. ¡Simplemente desapareció!";
			link.l1 = "Interesante... ¿Dónde puedo encontrar su casa?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "Vivía más arriba en la calle, en una choza justo detrás de la casa frente a la mansión con el balcón azul. No está lejos de aquí.";
			link.l1 = "Bien, no perderé el tiempo. Si descubro algo, te lo haré saber.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "¿Sospechoso? ¡Estaba rodeada de pretendientes, y cada uno era sospechoso a su manera! Era toda una coqueta, sabía cómo atraer la atención.";
			link.l1 = "Eso ya lo noté"+GetSexPhrase("","")+"... ¿Pero alguien destacaba especialmente?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Hmm... Bueno, había uno. Esa noche le regaló un colgante con camafeo. Estuvo aquí, sin apartar los ojos de ella, rondándola toda la noche.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "¿No será este el colgante? (Mostrar el camafeo comprado al mendigo)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Un colgante con camafeo, dices...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "¡Ese! ¡Exactamente ese! Capitán, ¿ya ha descubierto algo?";
			link.l1 = "Los detalles después, "+npchar.name+", ahora no hay tiempo que perder.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Entregado: Colgante con camafeo", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "¡Eso es excelente, Capitán! Ya empezaba a pensar que no la volvería a ver. Entonces, ¿qué pasó al final? ¿De verdad quería escapar?";
			link.l1 = "Digamos que tuvo que lidiar con algunos problemas de su pasado. Pero parece que todo eso ya quedó atrás y pronto podrá volver al trabajo.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Bueno, digamos que necesitaba un pequeño descanso de contemplar tu aburrido rostro. ¡Ja, ja! No pongas esa cara, es una broma. Cada dama debe tener sus pequeños secretos...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Lo importante es que regresará al trabajo. Ha ganado su recompensa, capitán. Aquí tiene, cien doblones, como acordamos. Además, tome este mapa. Uno de los clientes lo dejó aquí y nunca volvió. Todo indica que lleva a un tesoro.";
			link.l1 = "Bien, lo comprobaré. Gracias.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "Lo importante es que regresará al trabajo. Ha ganado su recompensa, capitán. Aquí tiene, cien doblones, como acordamos. Además, tome este mapa. Uno de los clientes lo dejó aquí y nunca volvió. Todo indica que lleva a un tesoro.";
			link.l1 = "Bien, lo comprobaré. Gracias.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			GiveItem2Character(PChar, "map_full");
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
