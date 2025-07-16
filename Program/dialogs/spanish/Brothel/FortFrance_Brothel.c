// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué tipo de preguntas, "+GetSexPhrase("joven","jovencita")+"?","¿Qué necesitas, "+GetSexPhrase("guapo","bonita")+"? Pregunta lo que quieras."),"¿Preguntas otra vez?","Vaya, otra vez lo mismo... preguntas...",
                          ""+GetSexPhrase("Mm, ¿por qué no eliges una belleza para ti? Estoy empezando a sospechar de ti...","Mm, ¿por qué no eliges una belleza para ti? No tenemos chicos aquí, me temo, jeje...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión, discúlpame.","En realidad, olvídalo..."),"Yo... lo siento, no tengo preguntas, por ahora.",
                      "Tienes razón, es la tercera vez ya. Perdóname.","Tal vez la próxima vez, señora.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Escucha, Aurora, necesito una chica para esta noche. Y quiero llevármela a casa conmigo. ¿Puedes arreglar eso?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Por supuesto, querido. ¿Ya has encontrado una doncella adecuada o debo hacerlo yo?";
			link.l1 = "De hecho, lo hice. Tengo mis ojos puestos en una chica llamada Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "¿Te refieres a Lucille Montaigne?";
			link.l1 = "La verdad sea dicha, no le pregunté su apellido. Todo lo que sé es que es una joven, hermosa y rubia llamada Lucille.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Sí, eso la describe muy bien. Está bien. Pero dime, ¿por qué ella? ¿Es que las otras chicas no son de tu agrado?";
			link.l1 = "Bueno, verás... ella acaba de empezar a trabajar aquí, así que creo que aún no tiene suficiente experiencia en el 'oficio' como para ser una carga demasiado grande para mi bolsa.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Verás, adoro a las rubias de piel clara. Lucille será perfecta en ese sentido.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "¡Bueno, monsieur, eso no es cierto! Ella es joven, bonita y experimentada, mis clientes la admiran sin excepción. Te costará mucho. Cinco mil pesos por una noche con ella, y ni un solo peso menos.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Caro, pero muy bien. Aquí tienes tus monedas.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "¡Eso es muy caro! No tengo tanto. Hablaré contigo más tarde.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Bueno, tienes razón, monsieur. Es bonita y joven, pero le falta experiencia. Mis clientes generalmente no la notan, por eso pregunté. Pero si realmente te gustan las chicas modestas, digo que es una buena elección. Te costará dos mil quinientos pesos.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "Muy bien. Toma tus monedas.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "¡Eso es muy caro! No tengo tanto. Hablaré contigo más tarde.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "No serías el primero, guapo. A veces mis clientes hacen cola por su atención, ya que es muy distinta de las hijas de piel oscura de nuestras islas. Te costará cuatro mil quinientos pesos.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Caro, pero muy bien. Aquí tienes tus monedas.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "¡Eso es muy caro! No tengo tanto. Hablaré contigo más tarde.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "¿De veras, monsieur? ¿Ya tienes nostalgia? Mis criollas, y especialmente mis mulatas son más apasionadas que esta gata callejera parisina. Pero, hey, es tu elección. Te costará tres mil pesos.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "Caro, pero muy bien. Aquí tienes tus monedas.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "¡Eso es muy caro! No tengo tanto. Hablaré contigo más tarde.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Como desees, querido. Lucille te estará esperando ansiosamente a las once de la noche. Si no llegas antes de la medianoche, atenderá a otro cliente, y entonces tendrás que esperar hasta la próxima noche para llevártela. Además, debe regresar antes de las siete de la mañana. Y no pienses en... hacerle daño, de ninguna manera. O lo lamentarás. Una advertencia justa, querido.";
			link.l1 = "No te preocupes, la trataré como a una amante, no como a un bruto. La recogeré a las once en punto. ¿Qué debería hacer hasta entonces?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Bueno, y yo qué sé, querido. Pasa por la taberna, charla con el tabernero...";
			link.l1 = "No es mala idea. Haré justo eso. ¡Que tengas un buen día!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
